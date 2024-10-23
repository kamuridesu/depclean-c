#ifndef CHAR_LIST_H
#define CHAR_LIST_H

typedef enum char_list_errors_e {
    CHAR_LIST_OK = 0,
    CHAR_LIST_UNK_ERR,
    CHAR_LIST_OUT_OF_BOUNDS,
    CHAR_LIST_ERR_COUNT,
} char_list_errors_e;

typedef struct CharList {
    int size;
    int capacity;
    char **content;
} CharList;

CharList* init_char_list();
char_list_errors_e add_to_list(CharList *list, const char *item);
char_list_errors_e free_char_list(CharList *list);


#endif
