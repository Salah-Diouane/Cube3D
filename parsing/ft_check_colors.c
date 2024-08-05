/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:37:07 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/05 12:06:54 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_color *ft_new_color(char *identif, int r, int g, int b)
{
    t_color *new_node;

    new_node = (t_color *)g_malloc(sizeof(t_color), MALLOC);
    if (!new_node)
        return (NULL);
    new_node->identif = ft_strdup(identif);
    new_node->r = r;
    new_node->g = g;
    new_node->b = b;
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
    int count;
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

int process_color_line(t_data *data, char *line, int *c_count, int *f_count)
{
    char **tmp;
    char **col;
    t_color *color = NULL;

    if (!strncmp(line, "C", 1))
        (*c_count)++;
    else if (!strncmp(line, "F", 1))
        (*f_count)++;
    tmp = ft_split(line, ' ');
    if (tmp[2] != NULL || (!tmp[0] || !tmp[1]))
        return printf("COLORS : error more than one argument in texture\n");
    col = ft_split(tmp[1], ',');
    if (col[0] && col[1] && col[2])
    {
        if ((atoi(col[0]) < 0 || atoi(col[0]) > 255) || (atoi(col[1]) < 0
			|| atoi(col[1]) > 255) || (atoi(col[2]) < 0 || atoi(col[2]) > 255))
            return printf("invalid rgb \n");
        color = ft_new_color(tmp[0], atoi(col[0]), atoi(col[1]), atoi(col[2]));
    }
    if (color)
        ft_add_color(&data->colors, color);
    else
        return printf("Memory allocation failed\n");
    ft_free_2d(tmp);
    ft_free_2d(col);
    return (0);
}

int ft_get_colors(t_data *data, char **map)
{
    int i;
    int c_count;
    int f_count;

    c_count = 0;
    f_count = 0;
    i = 0;
    while (map[i])
    {
        map[i][strlen(map[i])] = '\0';
        if (!strncmp(map[i], "C", 1) || !strncmp(map[i], "F", 1))
        {
            if (process_color_line(data, map[i], &c_count, &f_count))
                return (1);
        }
        i++;
    }
    if (c_count != 1 || f_count != 1)
        return (printf("Error: There must be exactly one 'C' and one 'F'\n"));
    return (0);
}
