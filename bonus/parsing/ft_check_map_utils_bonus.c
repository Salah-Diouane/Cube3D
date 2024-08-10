/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:22:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/08 15:23:19 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int ft_get_rows(char **map)
{
	int rows;
	
	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
}

int set_player_position(t_data *data)
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
			if (data->s_map->map[i][j] == 'N' || data->s_map->map[i][j] == 'S'||
                 data->s_map->map[i][j] == 'E' || data->s_map->map[i][j] == 'W')
			{
				cmp++;
				data->plr.x = (double)(j * 64 + 32);
				data->plr.y = (double)(i * 64 + 32);
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
