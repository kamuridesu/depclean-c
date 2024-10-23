#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct InfiniteProgress {
    int size;
    int direction;
    int position;
    int finish;
    pthread_mutex_t mu;
} InfiniteProgress;

InfiniteProgress newInfiniteProgress() {
    InfiniteProgress infiniteProgress;
    infiniteProgress.direction = 1;
    infiniteProgress.size = 40;
    infiniteProgress.finish = 0;
    infiniteProgress.position = 0;
    pthread_mutex_init(&infiniteProgress.mu, NULL);
    return infiniteProgress;
}

void updateInfiniteProgress(InfiniteProgress* ip) {
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
    ip->position += ip->direction;
    if (ip->position > ip->size || ip->position <= 0) {
        ip->direction *= -1;
    }
}

void endInfiniteProgress(InfiniteProgress* ip) {
    pthread_mutex_lock(&ip->mu);
    ip->finish = 1;
    printf("\n");
    pthread_mutex_unlock(&ip->mu);
    pthread_mutex_destroy(&ip->mu);
}

void startInfiniteProgress(InfiniteProgress *ip) {
    while (ip->finish != 1) {
        pthread_mutex_lock(&ip->mu);
        updateInfiniteProgress(ip);
        pthread_mutex_unlock(&ip->mu);
        usleep(1000);
    }
}

void* startInfiniteThread(void* param) {
    InfiniteProgress* ip = (InfiniteProgress*)param;
    startInfiniteProgress(ip);
    return 0;
}

int main(int argc, char** argv) {
    InfiniteProgress ip = newInfiniteProgress();
    pthread_t inf_thread;
    pthread_create(&inf_thread, NULL, startInfiniteThread, &ip);
    
    int counter = 0;
    while (1) {
        counter++;
        if (counter > 500) {
            endInfiniteProgress(&ip);
        }
        usleep(1000);
    }
    pthread_join(inf_thread, NULL);
}