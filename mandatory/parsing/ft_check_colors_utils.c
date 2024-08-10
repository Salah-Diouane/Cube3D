/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:18:09 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/10 02:43:54 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int ft_atoi(char *str)
{
    int res;
    int negative;
    
    if (!str)
        return (-1);
    negative = 1;
    res = 0;
    while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
                    *str == '\v' || *str == '\f' || *str == '\r'))
        ++str;
    if (*str == '-')
        negative = -1;
    if (*str == '-' || *str == '+')
        ++str;
    while (*str && *str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - 48);
        ++str;
    }
    return (res * negative);
}

t_color *ft_new_color(char *identif, int r, int g, int b)
{
    t_color *new_node;

    new_node = (t_color *)malloc(sizeof(t_color));
    if (!new_node)
        return (NULL);
    new_node->identif = ft_strdup(identif);
    if (!new_node->identif)
    {
        free(new_node);
        return (NULL);
    }
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
