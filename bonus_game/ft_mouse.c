/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 08:07:30 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/08 20:07:44 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/bonus.h"

static int  horizontal(t_data *data, double angle, int x)
{
    int         bl;
    
    bl = 0;
    if (x < (data->wnd_wd / 2) && ++bl)
        data->plr.d = real_angle(data->plr.d + angle);
    else if (((data->wnd_wd / 2) < x) && ++bl)
        data->plr.d = real_angle(data->plr.d - angle);
    return (bl);
}

static int  vertical(t_data *data, int y)
{
    int         bl;
    
    bl = 0;
     if ((y < (data->wnd_ht / 2)) && \
        ((data->plr.h + 3) < data->wnd_ht) && ++bl)
        data->plr.h += fabs(data->plr.h - y) / 6;
    else if (((data->wnd_ht / 2) < y) && \
        (0 < (data->plr.h - 3)) && ++bl)
        data->plr.h -= fabs(data->plr.h - y) / 6;
    return (bl);
}

void    ft_mouse(t_data *data)
{
    int         x;
    int         y;
    int         b[2];
    double      unite;
    double      angle;

    unite = ((60 * (M_PI / 180)) / \
        data->wnd_wd);
    mlx_get_mouse_pos(data->mlx, &x, &y);
    angle = (abs((data->wnd_wd / 2) - x) * unite) / 6;
    b[0] = horizontal(data, angle, x);
    b[1] = vertical(data, y);
    if (b[0] || b[1])
    {
        ft_clear_image(data->proj_img);
        ft_clear_image(data->map_img);
        ft_cast_rays(data);
    }
}