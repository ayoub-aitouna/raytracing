#ifndef PARCE_H
#define PARCE_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

typedef struct pos
{
    double x;
    double y;
    double z;
} post_t;

void print_scene();
char *get_next_line(int fd);
size_t l_size(char **dst);
char **Append(char **dst, char *str);
# endif
