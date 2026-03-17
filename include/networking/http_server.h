#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "chunck_size.h"
#include "structures/bytes.h"
#include "http/http_req_handlers.h"
#include <netinet/in.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdio.h>

#define PORT 8000

enum IP{IPv4, IPv6};

int net_bind_ipv4(struct sockaddr_in* sockaddr, int socket_fd);

int net_bind_ipv6(struct sockaddr_in6* sockaddr, int socket_fd);

int net_server_create(void* sock_addr, enum IP ip_type);

int http_server_accept(int socketServer);

struct Bytes* http_server_read_header(int fd);

void http_server_send_response(struct Bytes* string, int fd);

#endif