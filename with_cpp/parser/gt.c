#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 30
char *get_next_line(int fd)
{
    char buff;
    char *str;
    char r[7000000];
    int i;
    int n;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return 0;
    n = read(-1, str, BUFFER_SIZE);
    i = 0;
    n = read(fd, &buff, 1);
    while (n > 0)
    {
        r[i++] = buff;
        if (buff == '\n')
            break;
        n = read(fd, &buff, 1);
    }
    r[i] = 0;
    if (n <= 0 && i == 0)
        return 0;
    return (strdup(r));
}
