/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:07:16 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/02 10:01:13 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


int	ft_check_len_color(t_color	*color)
{
	t_color	*tmp;

	tmp = color;
	while (tmp)
	{
		if (ft_strlen(tmp->identif) != 1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_len_txt(t_text	*color)
{
	t_text	*tmp;

	tmp = color;
	while (tmp)
	{
		if (ft_strlen(tmp->identif) != 2)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

// mli kan7t NO SO EA WE wst map makhashach doz


int is_texture_or_color_line(char *line)
{
    if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
        strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 ||
        strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0)
    {
        return 1;
    }
    return 0;
}

int is_map_line(char *line)
{
    while (*line)
    {
        if (*line != '1' && *line != '0' && *line != ' ' && *line != '\t')
        {
            return 0;
        }
        line++;
    }
    return 1;
}

int validate_map_position(char **map)
{
    int i = 0;
    int map_started = 0;

    while (map[i])
    {
        i++;
    }

    // Check if map has started
    if (!map_started)
        return -1;  // No map lines found

    return 0; // Map is at the end
}

int ft_get_input(t_data *data, char **arv)
{
	char    **map;

	map = ft_read_map(arv);
	int i = 0;
	if (!map)
		return (printf("invalid map !!!\n"));
	// if (validate_map_position(map) != 0)
	// 	return (printf("ft_check_order fails!!\n"));
	if (ft_get_map(data, map) != 0)
		return (printf("ft_get_map fails!!\n"));
	if (ft_get_texture(data, map) != 0 || ft_count_text_size(data->text) != 4
			|| ft_check_len_txt(data->text) == -1)
		return (printf("ft_get_texture fails!!\n"));
	if (ft_get_colors(data, map) != 0 || ft_count_color_size(data->colors) != 2
			|| ft_check_len_color(data->colors) == -1)
		return (printf("ft_get_colors fails!!\n"));
	return (0);
}
