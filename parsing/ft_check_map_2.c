/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:15:30 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/02 08:30:39 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int set_player_position(t_data *data, char **cp_map)
{
	int i;
	int j;
	int	cmp;

	(1) && (i = 0, cmp = 0);
	while (cp_map[i] != NULL)
	{
		j = 0;
		while (cp_map[i][j])
		{
			if (cp_map[i][j] == 'N' || cp_map[i][j] == 'S' || cp_map[i][j] == 'W' || cp_map[i][j] == 'E')
			{
				(1) && (cmp++, data->plr.x = (double)j, data->plr.y = (double)i);
				data->plr.d = ft_get_direction(cp_map, &i, &j);
			}
			j++;
		}
		i++;
	}
	if (cmp != 1)
		return (printf("more than one player !!!\n"));
	return 0;
}

int check_walls_and_elements(t_data *data, char **cp_map)
{
	if (check_walls(cp_map) != 0)
		return -1;
	if (check_elements(cp_map) != 0)
		return -1;
	if (set_player_position(data, cp_map) != 0)
		return -1;
	return 0;
}
int initialize_cp_map(t_data *data, char ***cp_map, int *rows)
{
	*rows = ft_get_rows(data->map);

	*cp_map = (char **)malloc(sizeof(char *) * (*rows + 1));
	if (!*cp_map)
		return (printf("malloc error\n"));
	return (0);
}

int check_first_last_line(char **cp_map, int j)
{
	if (!is_all_ones(cp_map[0]) || !is_all_ones(cp_map[j - 1]))
	{
		for (int k = 0; k < j; k++)
			free(cp_map[k]);
		free(cp_map);
		return (printf("The first or last line is not all ones.\n"));
	}
	return 0;
}

int ft_first_check_map(t_data *data)
{
	char **cp_map;
	int i = 0, j = 0;
	int rows;

	if (initialize_cp_map(data, &cp_map, &rows) != 0)
		return (-1);
	if (populate_cp_map(data, cp_map, &i, &j) != 0)
		return (-1);
	if (check_first_last_line(cp_map, j) != 0)
		return (-1);
	if (check_walls_and_elements(data, cp_map) != 0)
		return (-1);
	return 0;
}
