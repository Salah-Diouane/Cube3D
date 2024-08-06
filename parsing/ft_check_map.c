/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:45:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/06 16:52:26 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static double degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

static double ft_get_direction(char **cp_map, int *i, int *j)
{
	double angle;

	if (cp_map[*i][*j] == 'N')
		angle = degrees_to_radians(90);
	else if (cp_map[*i][*j] == 'S')
		angle = degrees_to_radians(270);
	else if (cp_map[*i][*j] == 'W')
		angle = degrees_to_radians(180);
	else if (cp_map[*i][*j] == 'E')
		angle = degrees_to_radians(0);
	return (angle);
}

static int set_player_position(t_data *data)
{
	int i;
	int j;
	int	cmp;

	(1) && (i = 0, cmp = 0);
	while (data->s_map->map[i] != NULL)
	{
		j = 0;
		while (data->s_map->map[i][j])
		{
			if (data->s_map->map[i][j] == 'N' || data->s_map->map[i][j] == 'S'
				|| data->s_map->map[i][j] == 'W'
					|| data->s_map->map[i][j] == 'E')
			{
				(1) && (cmp++, data->plr.x = (double)j,
					data->plr.y = (double)i);
				data->plr.d = ft_get_direction(data->s_map->map, &i, &j);
			}
			j++;
		}
		i++;
	}
	if (cmp != 1)
		return (printf("more than one player !!!\n"));
	return (0);
}

static int ft_is_all_elem(t_data *data, int rows)
{
    int i;;
    int j;
    int nsew_count;

	i = 0;
	nsew_count = 0;
    data->doors_nbr = 0;
    data->v_bool.has_one = false;
    data->v_bool.has_zero = false;
    data->v_bool.has_nsew = false;

    while (i < rows)
    {
        j = 0;
        while (data->s_map->map[i][j] != '\0')
        {
            char c = data->s_map->map[i][j];
            if (c == '1')
                data->v_bool.has_one = true;
            else if (c == '0')
                data->v_bool.has_zero = true;
            else if (c == 'D')
                data->doors_nbr++;
            else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                nsew_count++;
                data->v_bool.has_nsew = true;
            }
            j++;
        }
        i++;
    }
    if (data->v_bool.has_one && data->v_bool.has_zero && data->v_bool.has_nsew
		&& (nsew_count == 1))
        return (0);
    return (1);
}

int ft_check_map(t_data *data)
{
	int		i;
	int		j;
	int		rows;

	(1) && (i = 0, j= 0);
	if (check_first_last_line(data->s_map->map) != 0)
		return (printf("invalid map !!!!!"));
	if (check_walls_and_elements(data->s_map->map) != 0)
		return (printf("invalid map !!!!!"));
	if (ft_check_around_elem(data->s_map->map) != 0)
		return (printf("invalid map !!!!!"));
	if (set_player_position(data) != 0)
		return (printf("invalid map !!!!!"));
	if (ft_is_all_elem(data, ft_get_rows(data->s_map->map)) != 0)
		return (printf("invalid map !!!!!"));
	return (0);
}
