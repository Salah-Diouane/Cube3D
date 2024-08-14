/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:22:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:59:10 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus_parser.h"

int	ft_get_rows(char **map)
{
	int	rows;

	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
}

static int	is_one_caracter_of_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	set_player_position(t_data *data)
{
	int	i;
	int	j;
	int	cmp;

	(1) && (i = 0, cmp = 0);
	while (data->map.arr[i] != NULL)
	{
		j = 0;
		while (data->map.arr[i][j])
		{
			if (is_one_caracter_of_player(data->map.arr[i][j]))
			{
				cmp++;
				data->plr.x = (double)(j * 64 + 32);
				data->plr.y = (double)(i * 64 + 32);
				data->plr.d = ft_get_direction(data->map.arr, &i, &j);
			}
			j++;
		}
		i++;
	}
	if (cmp != 1)
		return (printf("more than one player !!!\n"));
	return (0);
}
