/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:45:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:45:50 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus_parser.h"

double	ft_get_direction(char **cp_map, int *i, int *j)
{
	double	angle;

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

static void map_elmts(t_data *data, int rows, int *nsew_ct, int *flags)
{
	int	i;
	int	j;

	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (data->map.arr[i][++j] != '\0')
		{
			if (data->map.arr[i][j] == '1')
				flags[0] = 1;
			else if (data->map.arr[i][j] == '0')
				flags[1] = 1;
			else if (data->map.arr[i][j] == 'D')
				flags[2] = 1;
			else if (data->map.arr[i][j] == 'N' || \
					data->map.arr[i][j] == 'S' || \
					data->map.arr[i][j] == 'E' || \
					data->map.arr[i][j] == 'W')
			{
				(*nsew_ct)++;
				flags[3] = 1;
			}
		}
	}
}

static	int	ft_is_all_elem(t_data *data, int rows)
{
	int	i;
	int	j;
	int	flags[4];
	int	nsew_ct;

	i = nsew_ct = 0;
	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	flags[3] = 0;
	map_elmts(data, rows, &nsew_ct, flags);
	if (flags[0] && flags[1] && flags[2] && flags[3]
		&& (nsew_ct == 1))
		return (0);
	return (printf("you need more elem !!\n"));
}

int	ft_check_map(t_data *data)
{
	data->map.arr = ft_new_map(data, data->map.arr);
	if (!data->map.arr)
		return (printf("map failed !!\n"));
	if ((check_first_last_line(data->map.arr)) != 0)
		return (printf("check_first_last_line failed  !!!!!\n"));
	if ((ft_check_around_elem(data->map.arr)) != 0)
		return (printf("check_around_elem failed !!!!!\n"));
	if ((check_walls_and_elements(data->map.arr)) != 0)
		return (printf("check_walls_and_elements failed !!!!!\n"));
	if ((ft_is_all_elem(data, ft_get_rows(data->map.arr))) != 0)
		return (printf("ft_is_all_elem failed !!!!!\n"));
	return (0);
}
