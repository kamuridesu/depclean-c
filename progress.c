#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> // For testing 

typedef struct Progress {
    int status;
} Progress;

Progress startProgress() {
    const char *title = "Progress";
    printf("%s: [", title);
    for (int i = 0; i < 40; i++) {
        printf("-");
    }
    printf("]");
    for (int i = 0; i < 41; i++) {
        printf("\b");
    }
    Progress progress;
    progress.status = 0;
    return progress;
}

void updateProgress(Progress* p, int total, int current) {
    float percentage = ((100 * current) / total);
    int value = (int)percentage * 40 / 100;
    for (int i = 0; i < value - p->status; i++) {
        printf("#");
    }
    p->status = value;
}

void endProgress(Progress* p) {
    for (int i = 0; i < 40 - p->status; i++) {
        printf("#");
    }
    printf("]");
    p->status = 0;
}

int main(int argc, char** argv) {
    const int total = 100;
    Progress p = startProgress();
    for (int i = 0; i < total; i++) {
        updateProgress(&p, total, i);
        usleep(1000); // for testing
    }
    endProgress(&p);
}