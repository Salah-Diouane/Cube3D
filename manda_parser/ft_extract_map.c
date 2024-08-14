/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:35:28 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:13:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/manda_parser.h"

int	ft_is_identifier(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
			!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3) || \
			!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2));
}

int	ft_nbr_line(char **map)
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

int	just_one_zero(char *str)
{
	int	i;

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

int	ft_get_map(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->map.arr = (char **)malloc((ft_nbr_line(map) + 1) * sizeof(char *));
	if (!data->map.arr)
		return (printf("creation map allocation failed !\n"));
	while (map[i])
	{
		if (map[i] && !ft_is_identifier(map[i]))
		{
			data->map.arr[j] = ft_strdup(map[i]);
			if (!data->map.arr[j])
			{
				while (j > 0)
					free(data->map.arr[--j]);
				return (free(data->map.arr), printf("allocation failed!\n"));
			}
			j++;
		}
		i++;
	}
	data->map.arr[j] = NULL;
	return (0);
}
