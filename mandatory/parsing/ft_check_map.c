/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:45:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/08 15:29:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double ft_get_direction(char **cp_map, int *i, int *j)
{
	double angle;

	if (cp_map[*i][*j] == 'N')
		angle = 90 * (M_PI / 180.0);
	else if (cp_map[*i][*j] == 'S')
		angle = 270 * (M_PI / 180.0);
	else if (cp_map[*i][*j] == 'W')
		angle = 180 * (M_PI / 180.0);
	else if (cp_map[*i][*j] == 'E')
		angle = 0 * (M_PI / 180.0);
	return (angle);
}

static void initialize_map_flags(t_data *data)
{
    data->v_bool.has_one = false;
    data->v_bool.has_zero = false;
    data->v_bool.has_nsew = false;
    data->doors_nbr = 0;
}

static void process_map_elements(t_data *data, int rows, int *nsew_count)
{
    int i;
    int j;

    i = 0;
    while (i < rows)
    {
        j = 0;
        while (data->s_map->map[i][j] != '\0')
        {
            if (data->s_map->map[i][j] == '1')
                data->v_bool.has_one = true;
            else if (data->s_map->map[i][j] == '0')
                data->v_bool.has_zero = true;
            else if (data->s_map->map[i][j] == 'D')
                data->doors_nbr++;
            else if (data->s_map->map[i][j] == 'N' ||
                     data->s_map->map[i][j] == 'S' ||
                     data->s_map->map[i][j] == 'E' ||
                     data->s_map->map[i][j] == 'W')
            {
                (*nsew_count)++;
                data->v_bool.has_nsew = true;
            }
            j++;
        }
        i++;
    }
}

static int ft_is_all_elem(t_data *data, int rows)
{
    int     i;
    int     j;
    int     nsew_count;

	(1) && (i = 0, nsew_count = 0);
    initialize_map_flags(data);
    process_map_elements(data, rows, &nsew_count);
    if (data->v_bool.has_one && data->v_bool.has_zero && data->v_bool.has_nsew
		&& (nsew_count == 1))
        return (0);
    return (printf("you need more elem !!\n"));
}

int ft_check_map(t_data *data)
{
    data->s_map->map = ft_new_map(data, data->s_map->map);
    if (!data->s_map->map)
        return (printf("map failed !!\n"));
    if ((check_first_last_line(data->s_map->map)) != 0)
        return (printf("check_first_last_line failed  !!!!!\n"));
    if ((ft_check_around_elem(data->s_map->map)) != 0)
        return (printf("check_around_elem failed !!!!!\n"));
    if ((check_walls_and_elements(data->s_map->map)) != 0)
        return (printf("check_walls_and_elements failed !!!!!\n"));
    if ((ft_is_all_elem(data, ft_get_rows(data->s_map->map))) != 0)
        return (printf("ft_is_all_elem failed !!!!!\n"));
    return (0);
}
