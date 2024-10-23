#ifndef DIR_H
#define DIR_H

#include "list.h"
#include "progress.h"

int get_path_total_size(const char *root, CharList *folder_list, CharList *file_list);
int walk_dir(const char *root, CharList *folder_list, CharList *file_list);
void delete_all(CharList *folder_list, CharList *file_list, Progress *prog);

#endif
