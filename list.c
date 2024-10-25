#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

#define INITIAL_LIST_SIZE 2

CharList* init_char_list() {
    CharList *list = malloc(sizeof(CharList));
    list->size = 0;
    list->capacity = INITIAL_LIST_SIZE;
    list->content = malloc(list->capacity * sizeof(char*));
    return list;
}

char_list_errors_e add_to_list(CharList *list, const char *item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->content = realloc(list->content, list->capacity * sizeof(char*));
    }
    list->content[list->size] = strdup(item);
    list->size++;
    return CHAR_LIST_OK;
}

char_list_errors_e free_char_list(CharList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->content[i]);
    }
    free(list->content);
    free(list);
    return CHAR_LIST_OK;
}

char_list_errors_e remove_from_list(CharList *list, int index) {
    if (index > list->size || index < 0) {
        return CHAR_LIST_OUT_OF_BOUNDS;
    }
    free(list->content[index]);
    for (int i = index; i < list->size - 1; i++) {
        list->content[i] = list->content[i + 1];
    }
    list->size--;
    return CHAR_LIST_OK;
}

void print_list(CharList *list) {
    for (int i = 0; i < list->size; i++) {
        printf("%s\n", list->content[i]);
    }
}

// int main(int argc, char **argv) {
//     CharList *list = init_char_list();
//     add_to_list(list, "tsert");
//     add_to_list(list, "hello");
//     add_to_list(list, "world");
//     for (int i = 0; i < list->size; i++) {
//         printf("%s\n", list->content[i]);
//     }
//     remove_from_list(list, 0);
//     for (int i = 0; i < list->size; i++) {
//         printf("%s\n", list->content[i]);
//     }
//     free_char_list(list);
//     return 0;
// }
