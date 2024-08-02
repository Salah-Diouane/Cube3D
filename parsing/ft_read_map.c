/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:07:16 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/31 10:10:55 by sdiouane         ###   ########.fr       */
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

int is_map_line(char *line)
{
    while (*line)
    {
        if (*line != '1' && *line != '0' && *line != ' ' && *line != '\t'
			&& *line != 'P' && *line != 'N')
            return (0);
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
        if (is_map_line(map[i]))
            map_started = 1;
        else if (map_started && map[i][0] != '\0' && !is_map_line(map[i]))
            return (-1);
        i++;
    }
    return (0);
}

int ft_get_input(t_data *data, char **arv)
{
	char    **map;

	map = ft_read_map(arv);
	int i = 0;
	if (!map)
		return (printf("invalid map !!!\n"));
	if (validate_map_position(map) != 0)
		return (printf("ft_check_order fails!!\n"));
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
