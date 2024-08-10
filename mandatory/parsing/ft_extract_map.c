/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:35:28 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/08 15:25:27 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

int ft_get_map(t_data *data, char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    data->s_map->map = (char **)malloc((ft_count_map_line(map) + 1) * sizeof(char *));
    if (!data->s_map->map)
        return (printf("creation map allocation failed !\n"));
    while (map[i])
    {
        if (map[i] && !ft_is_identifier(map[i]))
        {
            data->s_map->map[j] = ft_strdup(map[i]);
            if (!data->s_map->map[j])
            {
                while (j > 0)
                    free(data->s_map->map[--j]);
                return (free(data->s_map->map), printf("allocation failed !\n"));
            }
            j++;
        }
        i++;
    }
    data->s_map->map[j] = NULL;
    return 0;
}
