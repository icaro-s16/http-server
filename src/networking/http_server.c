#include "networking/http_server.h"

int net_bind_ipv4(struct sockaddr_in* sockaddr, int socket_fd){
    sockaddr->sin_addr.s_addr = INADDR_ANY;
    sockaddr->sin_family = AF_INET;
    sockaddr->sin_port = htons(PORT);
    return bind(socket_fd, (struct sockaddr*) sockaddr, sizeof(struct sockaddr_in));
}

int net_bind_ipv6(struct sockaddr_in6* sockaddr, int socket_fd){
    sockaddr->sin6_addr = in6addr_any;
    sockaddr->sin6_family = AF_INET;
    sockaddr->sin6_port = htons(PORT);
    return bind(socket_fd, (struct sockaddr*) sockaddr, sizeof(struct sockaddr_in6));
}

int net_server_create(void* sock_addr, enum IP ip_type){
    int _domain = (ip_type == IPv4) ? AF_INET : AF_INET6;

    int socket_fd = socket(_domain, SOCK_STREAM, 0);
    if (socket_fd < 0) return socket_fd;

    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0){
        perror("[ERROR] fail to set socket options\n");
        close(socket_fd);
        return -1;
    }

    int bind_status;
    if (ip_type == IPv4)
        bind_status = net_bind_ipv4((struct sockaddr_in*) sock_addr, socket_fd);
    else 
        bind_status = net_bind_ipv6((struct sockaddr_in6*) sock_addr, socket_fd);

    if (bind_status < 0){
        perror("[ERROR] fail to bind the socket with it's address\n");
        close(socket_fd);
        return -1;
    }
    
    if (listen(socket_fd, 3) < 0){
        perror("[ERROR] fail to listen to clients\n");
        return -1;
    }

    return socket_fd;
}

int http_server_accept(int socketServer){
    return accept(socketServer, NULL, NULL);
}

struct Bytes* http_server_read_header(int fd){
    size_t buffer_size = CHUNCK_SIZE;
    size_t off_set = 0;

    char* buffer = calloc(buffer_size, sizeof(char));
    
    while(1){
        size_t bytes = recv(fd, &buffer[off_set], (buffer_size - off_set), 0);
        off_set += bytes;
        if (bytes == 0) break;
        if (http_is_header_complete(buffer) == 0) break;

        if (bytes == buffer_size) {
            buffer_size *= 2;
            char* aux = realloc(buffer, buffer_size);
            buffer = (aux != buffer) ? aux : buffer;

            memset(&buffer[off_set], 0, buffer_size - off_set);

        }
        
    }

    struct Bytes* bytes = bt_create(buffer, off_set);
    free(buffer);

    return bytes;

}

void http_server_send_response(struct Bytes* bytes, int fd){
    if (bytes->bytes == NULL || bytes->size == 0) {
        printf("[ERROR] Response sent invalidated\n");
        return;
    }
    send(fd, bytes->bytes, bytes->size, 0);
    printf("[LOG] Response sent successfully\n");
    
}