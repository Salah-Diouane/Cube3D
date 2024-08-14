/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:29:18 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/08 08:51:37 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/bonus.h"

int put_error(t_data *data, char *des, int set)
{
    if (1 <= set)
        free_map_text(data);
    if (2 <= set)
        free(data->inter_arr);
    if (3 <= set)
       free(data->door_arr);
    while (des && *des)
        write(2, des++, 1);
    return (-1);
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
    if (mlx_is_key_down(data->mlx, 265))
        ft_move_plr(265, data);
}

void    animation(t_data *data)
{
    int         key;
    static int  counter;
    
    key = -1;
    if (mlx_is_key_down(data->mlx, 32))
        data->gun.sht = 'S';
    if (mlx_is_mouse_down(data->mlx, \
        MLX_MOUSE_BUTTON_LEFT))
        ft_mouse(data);
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
    while (data && data->map.arr[ind[1]])
    {
        ind[0]++;
        if (data->map.arr[ind[1]][ind[0]] == 'd')
        {
            data->door_arr[ind[2]].i = ind[0];
            data->door_arr[ind[2]].j = ind[1];
            data->door_arr[ind[2]].var = 32;
            data->door_arr[ind[2]].state = 'C';
            ind[2]++;
        }
        if (!data->map.arr[ind[1]][ind[0] + 1] && ++ind[1])
            ind[0] = -1;
    }
}