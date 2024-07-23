/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/07/24 16:52:32 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

void ft_free_lst(t_face *lst)
{
    t_face      *tmp;
    
    while (lst && lst->next)
    {
        tmp = lst;
        lst = lst->next;
        free (tmp);
    }
}

static t_face   *ft_create_node(double x_ref, double y_ref)
{
    t_face      *node;
    
    node = (t_face *)malloc(sizeof(t_face));
    node->height_1 = -1;
    node->x_ref = x_ref;
    node->y_ref = y_ref;
    node->rays = 0;
    node->fix = 0;
    node->next = NULL;
    return (node);
}

static double get_height(t_data *data, int i)
{
    double      oppo;
    double      adja;
    double      result;

    adja = fabs(data->plr->x - data->array[i].x);
    oppo = fabs(data->plr->y - data->array[i].y);
    result = ((100 * 100) / sqrt((oppo * oppo) + \
        (adja * adja)));
    return (result);
} 

static int create_sub_fun(t_data *data, t_face **tmp, int i)
{
    if (((*tmp)->fix == 1) && (data->array[i].x == (*tmp)->x_ref))
    {   
        if ((i == 759) || (data->array[i + 1].x != (*tmp)->x_ref))
            (*tmp)->height_2 = get_height(data, i);
    }
    else if (((*tmp)->fix == 2) && (data->array[i].y == (*tmp)->y_ref))
    {   
        if ((i == 759) || ( data->array[i + 1].y != (*tmp)->y_ref))
            (*tmp)->height_2 = get_height(data, i);
    }
    else
    {
        (*tmp)->next = ft_create_node(data->array[i].x, \
            data->array[i].y);
        if (!(*tmp)->next)
            return (-1);
        (*tmp) = (*tmp)->next;
    }
    return (0);
}

void    ft_create_list(t_data *data)
{
    int         i;
    t_face      *tmp;

    i = -1;
    tmp = ft_create_node(data->array[0].x, \
        data->array[0].y);
    data->face_lst = tmp;
    while (++i < 760)
    {
        if (tmp->fix == 0)
        {
            ((data->array[i].x != tmp->x_ref) && (tmp->fix = 2));
            ((data->array[i].y != tmp->y_ref) && (tmp->fix = 1));
            if (tmp->height_1 == -1)
                tmp->height_1 = get_height(data, i);
            if ((i == 759) || (data->array[i + 1].x != tmp->x_ref))
                tmp->height_2 = get_height(data, i);
        }
        else
            create_sub_fun(data, &tmp, i);
        tmp->rays++;
    }
}

