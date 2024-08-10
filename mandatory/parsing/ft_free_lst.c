/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:40:53 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/08 15:16:29 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void free_text(t_text *node)
{
    if (node)
    {
        if (node->identif)
            free(node->identif);
        if (node->chem)
            free(node->chem);
        // if (node->pix_arr)
        // {
        //     free(node->pix_arr);
        // }
        // Free the node itself
        free(node);
    }
}

void free_texture(t_text *head)
{
    t_text *current;
    t_text *next;

    current = head;
    while (current)
    {
        next = current->next;
        free_text(current);
        current = next;
    }
}

void free_color(t_color *color)
{
    t_color *temp;

    while (color != NULL)
    {
        temp = color;
        color = color->next;
        if (temp->identif != NULL)
            free(temp->identif);
        free(temp);
    }
}

void free_map(t_map *map)
{
    int i;

    if (map != NULL)
    {
        if (map->map != NULL)
        {
            i = 0;
            while (map->map[i] != NULL)
            {
                free(map->map[i]);
                i++;
            }
            free(map->map);
        }
        free(map);
    }
}
