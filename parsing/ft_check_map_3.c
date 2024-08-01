/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:28:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/01 14:26:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


int ft_check_content(char *line)
{
	int i = 0;
	while (line && line[i])
	{
		if (strchr("10NSEW\n", line[i]))
			i++;
		else
			return (-1);
	}
	return (0);
}

int ft_get_rows(char **map)
{
	int rows = 0;
	while (map[rows])
		rows++;
	return rows;
}

int ft_get_cols(char **map)
{
	return (ft_strlen(map[0]));
}

int is_closed_by_walls(char **map, int rows, int cols)
{
	for (int j = 0; j < cols; j++)
	{
		if (map[0][j] != '1' || map[rows - 1][j] != '1')
			return 0;
	}

	for (int i = 0; i < rows; i++)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			return 0;
	}

	return 1;
}
