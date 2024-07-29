/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:37:07 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/29 18:33:13 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_color *ft_new_color(char *identif, char *value)
{
    t_color *new_node;

    new_node = (t_color *)malloc(sizeof(t_color));
    if (!new_node)
        return (NULL);
    new_node->identif = ft_strdup(identif);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;
    return (new_node);
}

void ft_add_color(t_color **head, t_color *new_node)
{
    t_color *current;

    if (!head || !new_node)
        return;
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

int ft_count_color_size(t_color *head)
{
    int     count;
    t_color *current;

    count = 0;
    current = head;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

int ft_get_colors(t_data *data, char **map)
{
    t_color *color;
    char **tmp;
    int i;

    (1) && (i = 0, color = NULL, tmp = NULL);
    while (map[i])
    {
		map[i][ft_strlen(map[i])] = '\0';
        if (!strncmp(map[i], "C", 1) || !strncmp(map[i], "F", 1))
        {
            tmp = ft_split(map[i], ' ');
			if (tmp[2] != NULL)
				return (printf("COLORS : error more than onr args in texture\n"));
			color = ft_new_color(tmp[0], tmp[1]);
			if (color)
				ft_add_color(&data->colors, color);
			else
				return (printf("Memory allocation failed\n"));
            free(tmp[0]);
            free(tmp[1]);
            free(tmp);
        }

        i++;
    }
    return (0);
}
