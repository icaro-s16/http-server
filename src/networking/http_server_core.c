#include "networking/http_server_core.h"

struct Worker* create_threads(){
    struct Worker* threads = calloc(N_THREADS, sizeof(struct Worker));
    for(int i = 0; i < N_THREADS; i++ ){
        pthread_mutex_init(&threads[i].content.lock, NULL);
    }
    return threads;
}



void destroy_threads(struct Manager* thread){
    if (thread == NULL) return;
    if (thread->workers != NULL){
        for ( int i = 0; i < N_THREADS ; i++){
            pthread_mutex_destroy(&thread->workers[i].content.lock);
        }
        free(thread->workers);
    }
}

struct Worker* tpool_acquire_worker(struct Worker* threads){
    for (int i = 0; i < N_THREADS; i++){
        if( pthread_mutex_trylock( &threads[i].content.lock ) == 0 )
            return &threads[i];
    }

    return NULL;
}


void* http_server_worker_routine(void* thread){
    pthread_mutex_lock( &((struct WorkerContent*)thread)->lock );

    struct Bytes* buffer = http_server_read_header( ((struct WorkerContent*)thread)->socket_client_fd );
    
    if (buffer == NULL || buffer->bytes == NULL){
        printf("[ERROR] Invalid read buffer\n");
        if (buffer != NULL) bt_destroy(buffer);
        close(((struct WorkerContent*) thread)->socket_client_fd);
        pthread_mutex_unlock( &((struct WorkerContent*) thread)->lock );
        return NULL;
    } 

    char* request_label = "Request: ";
    bt_prepend(buffer, request_label, strlen(request_label));

    struct Request* request = http_parse_request(buffer, ((struct WorkerContent*)thread)->maps.http_request_map);

    if (request == NULL || request->type == NULL || request->url == NULL){
        printf("[ERROR] Invalid request parser\n");
        bt_destroy(buffer);
        if (request != NULL) http_req_destroy(request);
        close(((struct WorkerContent*) thread)->socket_client_fd);
        pthread_mutex_unlock( &((struct WorkerContent*) thread)->lock );
        return NULL;
    }

    // To add POST in the future
    struct Packet* packet = http_packet_split(buffer);
    bt_destroy(buffer);


    struct Bytes* response = http_dispatch_request(((struct WorkerContent*)thread)->maps.http_response_map, ((struct WorkerContent*)thread)->maps.http_mime_map, packet, request);

    if (response == NULL || response->bytes == NULL){
        printf("[ERROR] Invalid response created\n");
        http_packet_destroy(packet);
        http_req_destroy(request);
        if (response != NULL) bt_destroy(response);
        close(((struct WorkerContent*) thread)->socket_client_fd);
        pthread_mutex_unlock( &((struct WorkerContent*) thread)->lock );
        return NULL;
    }
    
    http_server_send_response(response, ((struct WorkerContent*)thread)->socket_client_fd );

    bt_destroy(response);
    http_packet_destroy(packet);
    http_req_destroy(request);


    close(((struct WorkerContent*) thread)->socket_client_fd);

    pthread_mutex_unlock( &((struct WorkerContent*) thread)->lock );
    return NULL;
}

void* http_server_accept_routine(void* manager){
    while(1){
        int client_fd = http_server_accept(((struct Manager*)manager)->server_fd);

        struct Worker* current_worker;
        while ((current_worker = tpool_acquire_worker(((struct Manager*)manager)->workers)) == NULL);
        

        current_worker->content.socket_client_fd = client_fd;
        current_worker->content.maps.http_request_map = ((struct Manager*)manager)->maps.http_request_map;
        current_worker->content.maps.http_response_map = ((struct Manager*)manager)->maps.http_response_map; 
        current_worker->content.maps.http_mime_map = ((struct Manager*)manager)->maps.http_mime_map;

        pthread_mutex_unlock(&current_worker->content.lock);
        pthread_create(&current_worker->thread_id, NULL, http_server_worker_routine, &current_worker->content);
        pthread_detach(current_worker->thread_id);
        

        printf("[LOG] handling a request\n");
    }

    return NULL;
}




int server(){
    struct sockaddr_in serverAddr;
    struct sockaddr clientAddr;
    socklen_t clienAddrSize = sizeof(clientAddr);

    pthread_t manager_id;
    struct Manager manager;
    manager.workers = create_threads();
    manager.server_fd = net_server_create(&serverAddr, IPv4);
    manager.maps.http_request_map = http_init_req_router();
    manager.maps.http_response_map = http_init_res_router();
    manager.maps.http_mime_map = http_init_mime_router();

    pthread_create(&manager_id, NULL, http_server_accept_routine, &manager);

    printf("[LOG] Server is running on port 8000...\n");
    while(((char)getchar()) != 'q' );

    pthread_cancel(manager_id);
    pthread_join(manager_id, NULL);
    
    destroy_threads(&manager);
    close(manager.server_fd);
    hashmap_destroy(manager.maps.http_mime_map);
    hashmap_destroy(manager.maps.http_request_map);
    hashmap_destroy(manager.maps.http_response_map);
    
    

    return EXIT_SUCCESS;
}