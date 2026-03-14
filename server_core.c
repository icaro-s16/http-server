#include "include/networking/http_server.h"
#include "include/http/http_router.h"
#include "include/http/http_req_parser.h"
#include "include/http/http_res_dispatcher.h"
#include "include/http/http_res_builder.h"
#include "include/http/http_req_handlers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

#define N_THREADS 3

struct Thread{
    pthread_t thread;
    int socket_client_fd;
    pthread_mutex_t lock;
};

struct Thread* create_threads(){
    struct Thread* threads = calloc(N_THREADS, sizeof(struct Thread));
    for(int i = 0; i < N_THREADS; i++ ){
        pthread_mutex_init(&threads[i].lock, NULL);
    }
    return threads;
}

void http_server_worker_routine(void* thread){
    pthread_mutex_lock( &((struct Thread*)thread)->lock );
    
    struct HashMap* http_request_map = http_init_req_router();

    struct HashMap* http_response_map = http_init_res_router();

    struct String* buffer = http_server_read_header( ((struct Thread*)thread)->socket_client_fd );
    
    dstr_prepend("Request: ", buffer);
    
    struct Request* request = http_parse_request(buffer, http_request_map);

    
    struct Packet* packet = http_packet_split(buffer);
    dstr_destroy(buffer);


    struct String* response = http_dispatch_request(http_response_map, packet, request);
    
    http_server_send_response(response, ((struct Thread*)thread)->socket_client_fd );

    hashmap_destroy(http_request_map);
    hashmap_destroy(http_response_map);
    dstr_destroy(response);
    http_packet_destroy(packet);
    http_req_destroy(request);
    close(((struct Thread*) thread)->socket_client_fd);

    pthread_mutex_unlock( &((struct Thread*) thread)->lock );

}

struct Thread* tpool_acquire_worker(struct Thread* threads){
    for (int i = 0; i < N_THREADS; i++){
        if( pthread_mutex_trylock( &threads->lock) == 0 )
            return &threads[i];
    }

    return NULL;
}

int server(){

    struct Thread* threads = create_threads();

    struct sockaddr_in serverAddr;
    struct sockaddr clientAddr;
    socklen_t clienAddrSize = sizeof(clientAddr);

    int socketServer = net_server_create(&serverAddr, IPv4);

    int flags = fcntl(socketServer, F_GETFL, 0);
    fcntl(socketServer, F_SETFL, flags | O_NONBLOCK);
    
    int socketClient = http_server_accept(socketServer);
    
    if (socketClient < 0 || errno != EAGAIN || errno != EWOULDBLOCK ){
        perror("[ERROR] fail to accpet a connection\n");
        
        free(threads);
        close(socketServer);
        
        return EXIT_FAILURE;
    }

    if (socketClient < 0){

    }else{
        struct Thread* thread = tpool_acquire_worker(threads);
        if (thread != NULL){
            thread->socket_client_fd = socketClient;
            pthread_mutex_unlock(&thread->lock);
            pthread_create(thread->thread, NULL, http_server_worker_routine, thread);
        }
        else
            close(socketClient);
    }
        
    
    free(threads);
    close(socketServer);
    
    return EXIT_SUCCESS;
}