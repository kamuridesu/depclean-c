#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "list.h"
#include "progress.h"

#define VENV_DIR "venv"
#define DOT_VENV_DIR ".venv"
#define NODE_MODULES_DIR "node_modules"
#define DOT_ENV_DIR ".env"

int get_path_total_size(const char *root, CharList *folder_list, CharList *file_list) {
    int size = 0;
    struct dirent *entry;
    struct stat file_stat;
    char path[1024];
    DIR *dir = opendir(root);

    if (dir == NULL) {
        perror("opendir");
        return size;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(path, sizeof(path), "%s/%s", root, entry->d_name);

        if (lstat(path, &file_stat) == 0) {
            if (S_ISLNK(file_stat.st_mode)) {
                continue;
            }
            if (S_ISDIR(file_stat.st_mode)) {
                add_to_list(folder_list, path);
                size += get_path_total_size(path, folder_list, file_list);
            } else if (S_ISREG(file_stat.st_mode)) {
                add_to_list(file_list, path);
                size += file_stat.st_size;
            }
        } else {
            perror("stat");
        }
    }

    return size;

}

int walk_dir(const char *root, CharList *folder_list, CharList *file_list) {
    struct dirent *entry;
    struct stat file_stat;
    char path[1024];
    DIR *dir = opendir(root);
    int total_size = 0;

    if (dir == NULL) {
        perror("opendir");
        return total_size;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", root, entry->d_name);

        if (lstat(path, &file_stat) == 0) {
            if (S_ISLNK(file_stat.st_mode)) {
                continue;
            }
            if (S_ISDIR(file_stat.st_mode)) {
                if (strstr(path, VENV_DIR) != NULL
                    || strstr(path, NODE_MODULES_DIR) != NULL
                    || strstr(path, DOT_ENV_DIR) != NULL
                    || strstr(path, DOT_VENV_DIR) != NULL) {
                        add_to_list(folder_list, path);
                        total_size += get_path_total_size(path, folder_list, file_list);
                } else {
                    total_size += walk_dir(path, folder_list, file_list);
                }
            }
        } else {
            perror("stat");
        }
    }
    closedir(dir);
    return total_size;
}

void delete_all(CharList *folder_list, CharList *file_list, Progress *prog) {
    int total_len = folder_list->size + file_list->size;
    int current_len = 0;
    for (int i = 0; i < file_list->size; i++) {
        update_progress(prog, total_len, current_len);
        unlink(file_list->content[i]);
        current_len++;
    }
    for (int i = 0; i < folder_list->size; i++) {
        update_progress(prog, total_len, current_len);
        rmdir(folder_list->content[i]);
        current_len++;
    }
    update_progress(prog, total_len, total_len);
}

// int main(int argc, char **argv) {
//     if (argc < 2) {
//         fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
//         exit(EXIT_FAILURE);
//     }
//     CharList *folder_list = init_char_list();
//     CharList *file_list = init_char_list();
//     int total_size = walk_dir(argv[1], folder_list, file_list);

//     for (int i = 0; i < folder_list->size; i++) {
//         printf("%s\n", folder_list->content[i]);
//     }
//     for (int i = 0; i < file_list->size; i++) {
//         printf("%s\n", file_list->content[i]);
//     }
//     printf("Total size: %d\n", total_size);

//     // delete_all(folder_list, file_list);

//     free_char_list(folder_list);
//     free_char_list(file_list);
//     return 0;
// }
