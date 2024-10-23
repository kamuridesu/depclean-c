#ifndef PROGRESS_H
#define PROGRESS_H

typedef struct Progress {
    int status;
} Progress;

Progress init_progress(char *title);
void update_progress(Progress *p, int total, int current);
void end_progress(Progress *p);

#endif
