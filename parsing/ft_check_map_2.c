/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:15:30 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/05 09:22:07 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int initialize_cp_map(t_data *data, char ***cp_map, int *rows)
{
	*rows = ft_get_rows(data->map);

	*cp_map = (char **)malloc(sizeof(char *) * (*rows + 1));
	if (!*cp_map)
		return (printf("malloc error\n"));
	return (0);
}

int populate_cp_map(t_data *data, char **cp_map, int *i, int *j)
{
	while (data->map[*i])
	{
		if (just_space(data->map[*i]) != -1)
			(*i)++;
		else
			break;
	}
	while (data->map[*i])
	{
		cp_map[*j] = trim_whitespace(data->map[*i]);
		if (cp_map[*j] == NULL)
		{
			ft_free_2d(cp_map);
			return (printf("Memory allocation error.\n"));
		}
		(*j)++;
		(*i)++;
	}
	cp_map[*j] = NULL;
	return (0);
}

int check_first_last_line(char **cp_map, int j)
{
	if (!is_all_ones(cp_map[0]) || !is_all_ones(cp_map[j - 1]))
	{
		return (printf("The first or last line is not all ones.\n"));
	}
	return 0;
}

double degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

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

double ft_get_direction(char **cp_map, int *i, int *j)
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

int ft_first_check_map(t_data *data)
{
	char **cp_map;
	int i = 0, j = 0;
	int rows;

	if (initialize_cp_map(data, &cp_map, &rows) != 0)
	{
		ft_free_2d(cp_map);
		return (-1);
	}
	if (populate_cp_map(data, cp_map, &i, &j) != 0)
	{
		ft_free_2d(cp_map);
		return (-1);
	}
	if (check_first_last_line(cp_map, j) != 0)
	{
		ft_free_2d(cp_map);
		return (-1);
	}
	if (check_walls_and_elements(data, cp_map) != 0)
	{
		ft_free_2d(cp_map);
		return (-1);
	}
	ft_free_2d(cp_map);
	return 0;
}
