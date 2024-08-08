/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:24:47 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/08 15:46:25 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static int count_lines(int fd)
{
    int len;
    char *line;

    len = 0;
    line = get_next_line(fd);
    while (line)
    {
        len++;
        free(line);
        line = get_next_line(fd);
    }
    return len;
}

static char **read_lines(int fd, int len)
{
    char **all;
    char *line;
    int i;

    all = malloc((len + 1) * sizeof(char *));
    if (!all)
        return (NULL);
    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        all[i++] = line;
        line = get_next_line(fd);
    }
    all[i] = NULL;
    return (all);
}

static int has_cube_extension(char *filename)
{
    int len_filename;
    int len_extension;

    len_filename = ft_strlen(filename);
    len_extension = ft_strlen(".cub");
    if (len_filename >= len_extension && 
        strncmp(filename + len_filename - len_extension, ".cube",
            len_extension) == 0)
        return (1);
    return (0);
}

static void	cub_check(char *map)
{
	if (strstr(map, ".cub") == 0
		&& printf("Format should be '.cub'\n"))
		exit(EXIT_FAILURE);
}

char **ft_read_map(char **arv)
{
    int fd;
    int len;
    char **all;

    cub_check(arv[1]);
    fd = open(arv[1], O_RDONLY, 0777);
    if (fd < 0)
        exit(EXIT_FAILURE);
    len = count_lines(fd);
    close(fd);
    fd = open(arv[1], O_RDONLY, 0777);
    if (fd < 0)
        exit(EXIT_FAILURE);
    all = read_lines(fd, len);
    close(fd);
    return (all);
}
