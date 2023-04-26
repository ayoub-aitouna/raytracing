#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include "parcer.hpp"

size_t l_size(char **dst)
{
	int i;

	i = 0;
	while (dst && dst[i])
		i++;
	return (i);
}

char **Append(char **dst, char *str)
{
	int		i;
	size_t	len;
	char	**result;

	if(!str)
		return dst;
	len	= l_size(dst);
	result = (char **) malloc( (len + 2) * sizeof(char *));

	while (dst && dst[i]) {
		result[i] = dst[i];
		i++;
	}
	result[i++] = strdup(str);
	result[i] = NULL;
	return (result);
}

char **read_sence(const char *file_name)
{
	char *line;
	char **scene;
	int fd;

	line = NULL;
	scene = NULL;
	fd = open(file_name, O_RDONLY);
	printf("%d \n", fd);

	while (1) {
		line = get_next_line(fd);
		if(!line)
			break;
		scene = Append(scene, line);	
		free(line);
	}
	return (scene);
}


void print_scene()
{
	char **scene = read_sence("scene.rt");
}
