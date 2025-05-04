#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "progress.h"

Progress init_progress(char *title) {
    printf("%s: [", title);
    for (int i = 0; i < 40; i++) {
        printf("-");
    }
    printf("]");
    for (int i = 0; i < 41; i++) {
        printf("\b");
    }
    fflush(stdout);
    Progress progress;
    progress.status = 0;
    return progress;
}

void update_progress(Progress *p, int total, int current) {
    float percentage = ((100 * current) / total);
    int value = (int)percentage * 40 / 100;
    for (int i = 0; i < value - p->status; i++) {
        printf("#");
    }
    fflush(stdout);
    p->status = value;
}

void end_progress(Progress *p) {
    for (int i = 0; i < 40 - p->status; i++) {
        printf("#");
    }
    printf("]\n");
    fflush(stdout);
    p->status = 0;
}

// int main(int argc, char **argv) {
//     const int total = 100;
//     char *title = "Progress";
//     Progress p = init_progress(title);
//     for (int i = 0; i < total; i++) {
//         update_progress(&p, total, i);
//         usleep(10000); // for testing
//     }
//     end_progress(&p);
// }
