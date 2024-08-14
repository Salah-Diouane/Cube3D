/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:07:16 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:13:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/manda_parser.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	just_space(char *str)
{
	while (*str)
	{
		if (!is_space((char)*str))
			return (-1);
		str++;
	}
	return (0);
}

static	int	is_texture_or_color(char *line)
{
	return (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || \
			!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) || \
			!ft_strncmp(line, "C", 1) || !ft_strncmp(line, "F", 1));
}

static	int	validate_elements_position(char **map)
{
	int	i;
	int	found_non_texture_or_color;

	i = 0;
	found_non_texture_or_color = 0;
	while (map[i])
	{
		if (just_space(map[i]) == 0)
		{
			i++;
			continue ;
		}
		if (is_texture_or_color(map[i]))
		{
			if (found_non_texture_or_color)
				return (-1);
		}
		else
			found_non_texture_or_color = 1;
		i++;
	}
	return (0);
}

int	ft_get_input(t_data *data, char **arv)
{
	char	**map;

	map = ft_read_map(arv);
	if (map[0] == (void *)0 && printf("empty map !!! \n"))
		(ft_free_2d(map), exit(EXIT_FAILURE));
	if (!map)
		return (printf("ft_read_map fails !!!\n"));
	if (validate_elements_position(map) != 0)
	{
		ft_free_2d(map);
		printf("invalid order !! \n");
		exit(0);
	}
	if (ft_get_map(data, map) != 0)
		return (ft_free_2d(map), printf("ft_get_map fails!!\n"));
	if (ft_get_texture(data, map) != 0)
		return (ft_free_2d(map), printf("ft_get_texture fails!!\n"));
	if (ft_get_colors(data, map) != 0)
		return (ft_free_2d(map)),
			printf("ft_get_colors fails!!\n");
	ft_free_2d(map);
	return (0);
}
