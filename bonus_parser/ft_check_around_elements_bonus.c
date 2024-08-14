/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_around_elements_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:11:43 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:33:38 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus_parser.h"

int	ft_check_position_of_elem(char **cp_map, char c, int *i, int *j)
{
	if (*i > 0 && (cp_map[*i - 1][*j] == ' ' || cp_map[*i - 1][*j] == '\t'
			|| cp_map[*i - 1][*j] == '\0'))
		return (printf("invalid_position of : -->%c<--\n", c));
	if (cp_map[*i + 1] != NULL && (cp_map[*i + 1][*j] == ' '
		|| cp_map[*i + 1][*j] == '\t' || cp_map[*i + 1][*j] == '\0'))
		return (printf("invalid_position of : -->%c<--\n", c));
	if (*j > 0 && (cp_map[*i][*j - 1] == ' ' || cp_map[*i][*j - 1] == '\t'
			|| cp_map[*i][*j - 1] == '\0'))
		return (printf("invalid_position of : -->%c<--\n", c));
	if (cp_map[*i][*j + 1] == ' ' || cp_map[*i][*j + 1] == '\t'
			|| cp_map[*i][*j + 1] == '\0')
		return (printf("invalid_position of : -->%c<--\n", c));
	return (0);
}

int	ft_check_around_elem(char **map)
{
	int	i;
	int	j;
	int	rows;
	int	cols;

	i = ft_skip_first_spaces(map);
	j = ft_skip_last_spaces(map);
	while (map[i] != NULL && i <= j)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || \
					map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
				if (ft_check_position_of_elem(map, map[i][j], &i, &j) != 0)
					return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
