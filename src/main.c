#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread_handler.h"

void example_task(void *args) {
    int *num = (int *)args;
    unsigned int delay = (rand() % 3 + 1);
    printf("processing task %d - working for %d\n", *num, delay);
    sleep(delay);
    free(args);
}

int main(void) {
    thread_handler_threadpool thread_pool;

    thread_handler_status status = init_thread_handler(&thread_pool);
    if (status == THREAD_HANDLER_ERROR) {
        fprintf(stderr, "Error: init_thread_handler\n");
        return EXIT_FAILURE;
    }
    status = start_thread_pool(&thread_pool);
    if (status == THREAD_HANDLER_ERROR) {
        fprintf(stderr, "Error: start_thread\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 100; i++) {
        int *task_num = malloc(sizeof(int));
        *task_num = i;
        enque_threadpool_task(&thread_pool, example_task, task_num);
    }

    while (1) {
        sleep(1);
        if (thread_pool.queue_count == 0) {
            status = stop_thread_pool(&thread_pool);
            if (status == THREAD_HANDLER_ERROR) {
                fprintf(stderr, "Error: stop_thread_pool\n");
                return EXIT_FAILURE;
            }
            break;
        }
    }

    return EXIT_SUCCESS;
}
