#include <stdio.h>
#include <math.h>
#include <stdlib.h>


char* formatSize(int number) {
    char* units[8] = {"", "Ki", "Mi", "Gi", "Ti", "Pi", "Ei", "Zi"};
    float n = number;
    char* buffer = (char*)malloc(100 * sizeof(char));
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
    char* strptr = formatSize(1024 * 1024 * 1034);
    printf("%s\n", strptr);
    free(strptr);
}
