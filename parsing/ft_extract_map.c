/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:35:28 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/29 18:28:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	**ft_read_map(char **arv)
{
	char	*line;
	char	*tmp;
	char	**all;
	int     fd;

	fd = open(arv[1], O_RDONLY, 0777);
	line = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		line = ft_strjoin(line, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	all = ft_split(line, '\n');
	free(line);
	return (all);
}

int ft_is_identifier(char *line)
{
    return (!strncmp(line, "NO ", 3) || !strncmp(line, "SO ", 3) ||
            !strncmp(line, "WE ", 3) || !strncmp(line, "EA ", 3) ||
            !strncmp(line, "F ", 2) || !strncmp(line, "C ", 2));
}

int ft_count_map_line(char **map)
{
	int	i;
	int	map_lines;

	map_lines = 0;
	i = 0;
    while (map[i])
    {
        if (!ft_is_identifier(map[i]))
            map_lines++;
        i++;
	}
	return (map_lines);
}

int ft_get_map(t_data *data, char **map)
{
    int i;
    int j;

    (1) && (i = 0, j = 0);
    data->map = (char **)malloc((ft_count_map_line(map) + 1) * sizeof(char *));
    if (!data->map)
        return (printf("Memory allocation failed!\n"));
    i = 0;
    while (map[i])
    {
        if (!ft_is_identifier(map[i]) )
        {
            data->map[j] = ft_strdup(map[i]);
            if (!data->map[j])
                return (printf("Memory allocation failed!\n"));
            j++;
        }
        i++;
    }
    data->map[j] = NULL;
    return (0);
}
