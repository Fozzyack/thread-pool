#include <stdio.h>
#include <stdlib.h>

#include "thread_handler.h"
int main(void) {
    thread_handler_threadpool thread_pool;

    thread_handler_status status = init_thread_handler(&thread_pool);
    if (status == THREAD_HANDLER_ERROR) {
        fprintf(stderr, "Error: init_thread_handler\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
