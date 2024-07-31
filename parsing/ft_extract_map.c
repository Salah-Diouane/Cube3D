/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:35:28 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/31 11:56:36 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	**ft_read_map(char **arv)
{
	int     fd;
	int     len;
	char	*line;
	char	**all;

	(1) && (fd = open(arv[1], O_RDONLY, 0777), len = 1,
		line = get_next_line(fd));
	while (line)
		(1) && (len++, free(line), line = get_next_line(fd));
	(1) && (free(line), close (fd), all = malloc(len * sizeof(char **)));
	(1) && (len = 0, fd = open(arv[1], O_RDONLY, 0777),
		line = get_next_line(fd));
	while (line)
	{
		all[len] = line;
		line = get_next_line(fd);
		len++;
	}
	(1) && (all[len] = NULL, free(line), close (fd));
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


int just_one_zero(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
			i++;
		else
			return (-1);
	}
	return (1);
}

// int ft_check_map(t_data *data)
// {
//     int i;

//     i = 0;
//     if (just_one_zero(data->map[0]) == -1)
//         return (printf("invalid map!!\n"));
//     // while (data->map[i])
//     // {
//     //     if (map[i] !=)
//     // }
// }

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
