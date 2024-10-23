#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

#include "progress.h"
#include "inf_progress.h"
#include "dir.h"

char* format_size(int number) {
    char *units[8] = {"", "Ki", "Mi", "Gi", "Ti", "Pi", "Ei", "Zi"};
    float n = number;
    char *buffer = (char*)malloc(100 * sizeof(char));
    for (int i = 0; i < 8; i++) {
        if (abs(n) < 1024) {
            snprintf(buffer, 100, "%.1f%sB", n, units[i]);
            return buffer;
        }
        n = n / 1024;
    }
    snprintf(buffer, 100, "%.1fYiB", n);
    return buffer;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    InfiniteProgress inf_prog = init_infinite_progress();
    pthread_t inf_thread;
    pthread_create(&inf_thread, NULL, start_infinite_thread, &inf_prog);
    CharList *folder_list = init_char_list();
    CharList *file_list = init_char_list();
    int total_size = walk_dir(argv[1], folder_list, file_list);
    end_infinite_progress(&inf_prog);
    pthread_join(inf_thread, NULL);

    for (int i = 0; i < file_list->size; i++) {
        printf("%s\n", file_list->content[i]);
    }

    char* human_total_size = format_size(total_size);
    printf("%s will be freed, continue? [y/N]: ", human_total_size);
    char letter = getchar();
    if (letter != 'y') {
        return 0;
    }

    Progress prog = init_progress("Progress: ");
    delete_all(folder_list, file_list, &prog);
    end_progress(&prog);

    printf("Freed: %s\n", human_total_size);

    free_char_list(folder_list);
    free_char_list(file_list);
    free(human_total_size);

    return 0;
}
