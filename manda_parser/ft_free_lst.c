/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:40:53 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:13:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/manda_parser.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

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
