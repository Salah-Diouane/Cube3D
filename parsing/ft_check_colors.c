/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:37:07 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/02 10:13:24 by sdiouane         ###   ########.fr       */
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
    while (current && current->next)
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

// int ft_set_rgb_colors(t_data    *data)
// {
//     char    **colors;
//     int     i;

//     i = 0;
//     colors = ft_split(data->colors->value, ',');
//     if (!colors)
//         return (-1);
//     while (colors[i])
//     {
//         if (atoi(colors[i]) < 0 || atoi(colors[i]) > 255)
//             return (-1);
//         i++;
//     }
//     data->colors->r = atoi(colors[0]);
//     data->colors->g = atoi(colors[1]);
//     data->colors->b = atoi(colors[2]);
//     return (0);
// }

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
            {
                printf("hahahahahahaha\n");
                ft_add_color(&data->colors, color);
            }
			else
				return (printf("Memory allocation failed\n"));
            free(tmp[0]);
            free(tmp[1]);
            free(tmp);
        }

        i++;
    }
    // if (ft_set_rgb_colors(data) != 0)
    //     return (printf("invalid colors\n"));
    return (0);
}
