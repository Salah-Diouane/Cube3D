/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:07:16 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/06 12:33:24 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int just_space(char *str)
{
	while (*str)
	{
		if (!is_space((char)*str))
			return -1;
		str++;
	}
	return 0;
}

static int is_texture_or_color(char *line)
{
    return (!strncmp(line, "NO", 2) || !strncmp(line, "SO", 2) ||
            !strncmp(line, "WE", 2) || !strncmp(line, "EA", 2) ||
            !strncmp(line, "C", 1) || !strncmp(line, "F", 1));
}

static int validate_elements_position(char **map)
{
    int i = 0;
    int found_non_texture_or_color = 0;

    while (map[i])
    {
        if (just_space(map[i]) == 0)
        {
            i++;
            continue;
        }
        if (is_texture_or_color(map[i]))
		{
            if (found_non_texture_or_color)
                return (printf("invalid order !! \n"));
		}
        else
            found_non_texture_or_color = 1;
        i++;
    }
    return 0;
}

int ft_get_input(t_data *data, char **arv)
{
	char    **map;

	map = ft_read_map(arv);
	if (!map)
		return (printf("ft_read_map fails !!!\n"));
	if (validate_elements_position(map) != 0)
		return (-1);
	if (ft_get_map(data, map) != 0)
		return (printf("ft_get_map fails!!\n"));
	if (ft_get_texture(data, map) != 0 || ft_count_text_size(data->text) != 4)
		return (printf("ft_get_texture fails!!\n"));
	if (ft_get_colors(data, map) != 0 || ft_count_color_size(data->colors) != 2)
		return (printf("ft_get_colors fails!!\n"));
	return (0);
}
