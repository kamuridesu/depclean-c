#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "inf_progress.h"

InfiniteProgress init_infinite_progress() {
    InfiniteProgress infiniteProgress;
    infiniteProgress.direction = 1;
    infiniteProgress.size = 40;
    infiniteProgress.finish = 0;
    infiniteProgress.position = 0;
    pthread_mutex_init(&infiniteProgress.mu, NULL);
    return infiniteProgress;
}

infinite_progress_error_e update_infinite_progress(InfiniteProgress *ip) {
    if (ip->finish == 1) {
        return INFINITE_PROGRESS_FINISHED;
    }
    printf("\r");
    printf("[");
    for (int i = 0; i < ip->position; i++) {
        printf("-");
    }
    printf("#");
    for (int i = 0; i < ip->size + 1 - ip->position; i++) {
        printf("-");
    }
    printf("]");
    fflush(stdout);
    ip->position += ip->direction;
    if (ip->position > ip->size || ip->position <= 0) {
        ip->direction *= -1;
    }
    return INFINITE_PROGRESS_OK;
}

infinite_progress_error_e end_infinite_progress(InfiniteProgress *ip) {
    if (ip->finish == 1) {
        return INFINITE_PROGRESS_FINISHED;
    }
    pthread_mutex_lock(&ip->mu);
    ip->finish = 1;
    printf("\n");
    fflush(stdout);
    pthread_mutex_unlock(&ip->mu);
    pthread_mutex_destroy(&ip->mu);
    return INFINITE_PROGRESS_OK;
}

infinite_progress_error_e start_infinite_progress(InfiniteProgress *ip) {
    if (ip->finish == 1) {
        return INFINITE_PROGRESS_FINISHED;
    }
    while (ip->finish != 1) {
        pthread_mutex_lock(&ip->mu);
        update_infinite_progress(ip);
        pthread_mutex_unlock(&ip->mu);
        usleep(10000);
    }
    return INFINITE_PROGRESS_OK;
}

void* start_infinite_thread(void *param) {
    InfiniteProgress* ip = (InfiniteProgress*)param;
    start_infinite_progress(ip);
    return 0;
}

// int main(int argc, char **argv) {
//     InfiniteProgress ip = init_infinite_progress();
//     pthread_t inf_thread;
//     pthread_create(&inf_thread, NULL, start_infinite_thread, &ip);
    
//     int counter = 0;
//     while (1) {
//         counter++;
//         if (counter > 500) {
//             end_infinite_progress(&ip);
//             break;
//         }
//         usleep(10000);
//     }
//     pthread_join(inf_thread, NULL);
// }
