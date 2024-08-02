/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:28:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/02 08:29:24 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


int check_walls(char **cp_map)
{
	int i;

	i = 0;	
	while (cp_map[i] && cp_map[i][0])
	{
		if (cp_map[i][0] == '1' && cp_map[i][ft_strlen(cp_map[i]) - 1] == '1')
			i++;
		else
			return (printf("Map is not closed by walls. in |%s| \t %d \n",
				cp_map[i], i));
	}
	return (0);
}

int check_elements(char **cp_map)
{
	int i;

	i = 0;
	while (cp_map[i] != NULL)
	{
		if (ft_check_elements(cp_map[i]))
			i++;
		else
			return (printf("error \n"));
	}
	return (0);
}

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
	int rows;
	
	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
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
