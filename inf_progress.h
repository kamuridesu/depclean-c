#ifndef INFINITE_PROGRESS_H
#define INFINITE_PROGRESS_H

typedef struct InfiniteProgress {
    int size;
    int direction;
    int position;
    int finish;
    pthread_mutex_t mu;
    pthread_t thread;
} InfiniteProgress;

typedef enum infinite_progress_error_e {
    INFINITE_PROGRESS_OK = 0,
    INFINITE_PROGRESS_FINISHED,
    INFINITE_PROGRESS_ERROR_COUNT,
} infinite_progress_error_e;

InfiniteProgress init_infinite_progress();
infinite_progress_error_e end_infinite_progress(InfiniteProgress* ip);
void start_infinite_progress(InfiniteProgress *ip);
infinite_progress_error_e update_infinite_progress(InfiniteProgress *ip);

#endif
