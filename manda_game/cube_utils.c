/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:29:18 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/13 21:11:47 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cube.h"

int put_error(t_data *data, char *des, int set)
{
    if (1 <= set)
        free_map_text(data);
    if (2 <= set)
        free(data->inter_arr);
    while (des && *des)
        write(2, des++, 1);
    return (-1);
}

void  animate_plr(void  *arg)
{
    t_data      *data;

    data = (t_data *)arg;
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
