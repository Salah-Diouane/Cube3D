/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:45:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/05 09:16:16 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int populate_cp_map_without_trimming(t_data *data, char **cp_map,
	int *i, int *j)
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
		cp_map[*j] = data->map[*i];
		if (cp_map[*j] == NULL)
			return (printf("Memory allocation error.\n"));
		(*j)++;
		(*i)++;
	}
	cp_map[*j] = NULL;
	return (0);
}

int ft_check_position_of_zero(char **cp_map, int *i, int *j)
{
	if (*i > 0 && (cp_map[*i - 1][*j] == ' ' || cp_map[*i - 1][*j] == '\t'
			|| cp_map[*i - 1][*j] == '\0'))
		return (printf("invalid_zero_position\n"));
	if (cp_map[*i + 1] != NULL && (cp_map[*i + 1][*j] == ' '
			|| cp_map[*i + 1][*j] == '\t' || cp_map[*i + 1][*j] == '\0'))
		return (printf("invalid_zero_position\n"));
	if (*j > 0 && (cp_map[*i][*j - 1] == ' ' || cp_map[*i][*j - 1] == '\t'
			|| cp_map[*i][*j - 1] == '\0'))
		return (printf("invalid_zero_position\n"));
	if (cp_map[*i][*j + 1] == ' ' || cp_map[*i][*j + 1] == '\t'
			|| cp_map[*i][*j + 1] == '\0')
		return (printf("invalid_zero_position\n"));
	return (0);
}

int ft_second_check_map(t_data *data)
{
	char **cp_map;
	int i;
	int j;
	int rows;
	int cols;

	(1) && (i = 0, j = 0, rows = ft_get_rows(data->map),
		cols = ft_get_cols(data->map));
	if (populate_cp_map_without_trimming(data, cp_map, &i, &j) != 0)
		return (-1);
	(1) && (i = 0, cp_map[j] = NULL);
	while (cp_map[i] != NULL)
	{
		j = 0;
		while (cp_map[i][j] != '\0')
		{
			if (cp_map[i][j] == '0')
				if (ft_check_position_of_zero(cp_map, &i, &j) != 0)
					return (-1);
			j++;
		}
		i++;
	}
	// free(cp_map);
	return (0);
}

int ft_check_map(t_data *data)
{
	if (ft_first_check_map(data) != 0 || ft_second_check_map(data) != 0)
		return printf("invalid map !!!!!");
	return (0);
}
