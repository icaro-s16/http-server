#ifndef HTTP_SERVER_CORE_H
#define HTTP_SERVER_CORE_H

#include "networking/http_server.h"
#include "http/http_router.h"
#include "http/http_req_parser.h"
#include "http/http_res_dispatcher.h"
#include "http/http_res_builder.h"
#include "http/http_req_handlers.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h> 
#include <pthread.h>

#define N_THREADS 3

struct Manager{
    pthread_t thread;
    int server_fd;
    struct HashMap* http_request_map;
    struct HashMap* http_response_map;
    struct Thread* workers;
};

struct Thread{
    pthread_t thread;
    int socket_client_fd;
    struct HashMap* http_request_map;
    struct HashMap* http_response_map;
    pthread_mutex_t lock;
};


struct Thread* create_threads();

void destroy_threads(struct Manager* thread);

struct Thread* tpool_acquire_worker(struct Thread* threads);


void* http_server_worker_routine(void* thread);

void* http_server_accept_routine(void* manager);


int server();

#endif