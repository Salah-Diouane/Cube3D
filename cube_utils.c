/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:29:18 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/07 14:38:16 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

int ft_free_lst(t_face *lst)
{
    t_face      *tmp;
    
    while (lst && lst->next)
    {
        tmp = lst;
        lst = lst->next;
        free (tmp);
    }
    return (0);
}

void  animate_plr(t_data *data)
{
    if (mlx_is_key_down(data->mlx, 65))
        ft_move_plr(65, data);
    if (mlx_is_key_down(data->mlx, 68))
        ft_move_plr(68, data);
    if (mlx_is_key_down(data->mlx, 83))
        ft_move_plr(83, data);
    if (mlx_is_key_down(data->mlx, 87))
        ft_move_plr(87, data);
    if (mlx_is_key_down(data->mlx, 262))
        ft_move_plr(262, data);
    if (mlx_is_key_down(data->mlx, 263))
        ft_move_plr(263, data);
    if (mlx_is_key_down(data->mlx, 264))
        ft_move_plr(264, data);
    if (mlx_is_key_down(data->mlx, 265) )
        ft_move_plr(265, data);
}

void    animation(t_data *data)
{
    int         key;
    static int  counter;
    
    key = -1;
    (mlx_is_key_down(data->mlx, 32) && (key = 32));
    ((key == 32) && (data->gun.sht = 'S'));
    if (counter == 0)
    {
        ft_door_ctl(data);
        counter = 5;
        shut(data);
    }
    animate_plr(data);
    counter--;
}

double get_height(t_data *data, int i)
{
    double      dst;
    double      unit;
    double      oppo;
    double      adja;
    double      ray_angle;
    double      result;

    unit = (60.0 * (M_PI / 180.0)) / data->wnd_wd;
    ray_angle = real_angle(fabs((data->wnd_wd / \
        2.0) - i) * unit);
    adja = fabs(data->plr.x - data->inter_arr[i].x);
    oppo = fabs(data->plr.y - data->inter_arr[i].y);
    dst = sqrt((oppo * oppo) + (adja * adja)) * \
        cos(ray_angle);
    result = ((300.0 * 100.0) / dst);
    return (result);
}

void    fill_door_array(t_data *data)
{
    int         ind[3];

    ind[2] = 0;
    ind[1] = 0;
    ind[0] = -1;
    while (data && data->s_map->map[ind[1]])
    {
        ind[0]++;
        if (data->s_map->map[ind[1]][ind[0]] == 'D')
        {
            data->door_arr[ind[2]].i = ind[0];
            data->door_arr[ind[2]].j = ind[1];
            data->door_arr[ind[2]].var = 32;
            data->door_arr[ind[2]].state = 'C';
            ind[2]++;
        }
        if (!data->s_map->map[ind[1]][ind[0] + 1] && ++ind[1])
            ind[0] = -1;
    }
}