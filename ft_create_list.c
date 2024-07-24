/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/07/24 13:15:31 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static t_face   *ft_create_node(void)
{
    t_face      *node;
    
    node = (t_face *)malloc(sizeof(t_face));
    node->height_1 = -1;
    node->rays = 0;
    node->next = NULL;
    return (node);
}

static double get_height(t_data *data, int i)
{
    double      oppo;
    double      adja;
    double      pro_plan;
    double      result;

    adja = fabs(data->plr->x - data->array[i].x);
    oppo = fabs(data->plr->y - data->array[i].y);
    pro_plan = 760 / (2 * tan(30 * (M_PI / 180)));
    result = ((10 * pro_plan) / sqrt((oppo * oppo) + \
        (adja * adja)));
    return (result);
} 

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

void    ft_create_list(t_data *data)
{
    int         i;
    int         fx;
    t_point     ref;
    t_face      *tmp;
    double      pr_h;

    (1) && (i = -1, fx = 0);
    tmp = ft_create_node();
    data->face_lst = tmp;
    ref.x = data->array[0].x;
    ref.y = data->array[0].y;
    while (++i < 760)
    {
        if (fx == 0)
        {
            if (data->array[i].x != ref.x)
                fx = 2;
            else if (data->array[i].y != ref.y)
                fx = 1;
            if (tmp->height_1 == -1)
                tmp->height_1 = get_height(data, i);
            if ((i == 759) || (data->array[i + 1].x != ref.x))
                tmp->height_2 = get_height(data, i);
            tmp->rays++;
        }
        else if ((fx == 1) && (data->array[i].x == ref.x))
        {
            if ((i == 759) || (data->array[i + 1].x != ref.x))
                tmp->height_2 = get_height(data, i);
            tmp->rays++;
        }
        else if ((fx == 2) && (data->array[i].y == ref.y))
        {
            if ((i == 759) || ( data->array[i + 1].y != ref.y))
                tmp->height_2 = get_height(data, i);
            tmp->rays++;
        }
        else
        {
            ref.x = data->array[i].x;
            ref.y = data->array[i].y;
            tmp->next = ft_create_node();
    
            if (!tmp->next)
                break ;
            tmp = tmp->next;
            tmp->rays++;
            fx = 0;
        }
    }
    i = 0;
    t_face      *tmp1;
    tmp1 = data->face_lst;
    while (tmp1)
    {
        printf("h1 : %f\th2 : %f\trays : %d\n", tmp1->height_1, tmp1->height_2, tmp1->rays);
        i++;
        tmp1 = tmp1->next;
    }
    printf("nbr of faces : %d\n", i);
}

