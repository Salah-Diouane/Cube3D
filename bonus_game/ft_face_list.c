/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_face_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/05 15:40:25 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/bonus.h"

static void set_fix(t_face *tmp, t_point *arr, \
    t_point *ref, int i)
{
    if (arr[i].y != ref->y)
        tmp->fix = 'X';
    else if (arr[i].x != ref->x)
        tmp->fix = 'Y';
}

static t_face   *new_node()
{
    t_face      *node;
    
    node = malloc(sizeof(t_face));
    if (node)
    {
        node->fix = 'U';
        node->dir = 'U';
        node->rays = 0;
        node->next = NULL;
    }
    return (node);
}

static void set_dir(t_data *data, t_face *tmp, int i)
{
    if (tmp->fix == 'Y')
    {
        if (data->inter_arr[i].y < data->plr.y)
            tmp->dir = 'N';
        else if (data->plr.y < data->inter_arr[i].y)
            tmp->dir = 'S';
    }
    else
    {
        if (data->inter_arr[i].x < data->plr.x)
            tmp->dir = 'E';
        else if (data->plr.x < data->inter_arr[i].x)
            tmp->dir = 'W';
    }
}

static int new_face(t_data *dt, t_face **tp, \
    t_point *rf, int i)
{
    t_face      *new;

    rf->x = dt->inter_arr[i].x;
    rf->y = dt->inter_arr[i].y;
    new = new_node();
    if (!new)
        return (-1);
    else if ((*tp) == NULL)
        (*tp) = new;
    else
    {
        (*tp)->next = new;
        (*tp) = (*tp)->next;
    }
    return (0);
}

int  face_list(t_data *data)
{
    int         i;
    t_point     ref;
    t_point     *arr;
    t_face      *tmp;

    i = -1;
    tmp = NULL;
    arr = data->inter_arr;
    free_lnkd_lst(data->face_lst);
    if (new_face(data, &tmp, &ref, 0))
        return ((data->face_lst = NULL), -1);
    data->face_lst = tmp;
    while (data && arr && tmp && (++i < data->wnd_wd))
    {
        if (tmp->fix == 'U')
            set_fix(tmp, arr, &ref, i);
        else if (((arr[i].x != ref.x) || (arr[i].y != ref.y)) && \
            new_face(data, &tmp, &ref, i))
            return (-1);
        if ((tmp->dir == 'U') && (((tmp->fix == 'X') && \
            (arr[i].x == ref.x)) || ((tmp->fix == 'Y') && \
                (arr[i].y == ref.y))))
            set_dir(data, tmp, i);
        tmp->rays++;
    }
    return (0);
}
