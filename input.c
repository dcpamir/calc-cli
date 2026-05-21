#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ssize_t get_line(char **line, FILE *fp) {
    int buffer = 8;
    int len = 0;
    free(*line);
    *line = malloc(buffer);
    while (1) {
        if (fgets(*line + len, buffer - len, fp) == NULL) {
            return -1;
        }
        if (strchr(*line + len, '\n') != NULL) {
            return strlen(*line);
        }
        len = strlen(*line);
        buffer *= 2;
        *line = realloc(*line, buffer);
    }
}