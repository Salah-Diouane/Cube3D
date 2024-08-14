/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:40:53 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:34:36 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus_parser.h"

void	free_color(t_color	*color)
{
	t_color	*temp;

	while (color != NULL)
	{
		temp = color;
		color = color->next;
		if (temp->identif != NULL)
			free(temp->identif);
		free(temp);
	}
}

void	free_map(t_map	*map)
{
	int	i;

	if (map != NULL)
	{
		if (map->arr != NULL)
		{
			i = 0;
			while (map->arr[i] != NULL)
			{
				free(map->arr[i]);
				i++;
			}
			free(map->arr);
		}
		free(map);
	}
}
