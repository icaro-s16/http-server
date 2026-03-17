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

struct ThreadMaps{
    struct HashMap* http_mime_map;
    struct HashMap* http_request_map;
    struct HashMap* http_response_map;
};

struct WorkerContent{
    int socket_client_fd;
    struct ThreadMaps maps;
    pthread_mutex_t lock;
};

struct Worker{
    pthread_t thread_id;
    struct WorkerContent content;
};

struct Manager{
    int server_fd;
    struct ThreadMaps maps;
    struct Worker* workers;
};





struct Worker* create_threads();

void destroy_threads(struct Manager* thread);

struct Worker* tpool_acquire_worker(struct Worker* threads);


void* http_server_worker_routine(void* thread);

void* http_server_accept_routine(void* manager);


int server();

#endif