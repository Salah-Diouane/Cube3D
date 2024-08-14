/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_first_last_line_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:20:24 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:13:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/manda_parser.h"

int	ft_get_first_index(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (i);
		i++;
	}
	return (i);
}

int	ft_get_last_index(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line && i >= 0 && (line[i] == ' ' || line[i] == '\t' || \
			line[i] == '\n'))
		i--;
	return (i);
}

int	ft_skip_first_spaces(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (just_space(map[i]) != -1)
			i++;
		else
			break ;
	}
	return (i);
}
