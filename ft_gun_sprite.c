/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gun_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:22:31 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/06 08:42:09 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

int delete_imgs(t_data *data, int size)
{
    int         i;

    i = -1;
    while (++i < size)
        mlx_delete_image(data->mlx, \
            data->gun.arr[i]);
    return (0);
}

mlx_image_t *load_gun_sprite(mlx_t *mlx, char *path)
{
    mlx_image_t     *image;
    mlx_texture_t   *texture;

    image = NULL;
    texture = mlx_load_png(path);
    if (texture)
    {
        image = mlx_texture_to_image(mlx, texture);
        mlx_delete_texture(texture);
    }
    return (image);
}

int init_gun_arr(t_data *data)
{
    int     i;
    char    *str[] = {
        "gun/gun0.png", "gun/gun1.png", "gun/gun2.png", \
        "gun/gun3.png", "gun/gun4.png", "gun/gun5.png", \
        "gun/gun6.png", "gun/gun7.png", "gun/gun8.png", \
        "gun/gun9.png", "gun/gun10.png", "gun/gun11.png", \
        "gun/gun12.png"};
        
    i = -1;
    while (++i < 13)
    {
        data->gun.arr[i] = load_gun_sprite(data->mlx, str[i]);
        if (!data->gun.arr[i])
            return (delete_imgs(data, i), -1);
        data->gun.arr[i]->enabled = 0;
        mlx_image_to_window(data->mlx, data->gun.arr[i], \
            ((data->wnd_wd / 2) - (data->gun.arr[i]->width / 2)), \
            (data->wnd_ht - data->gun.arr[i]->height));
    }
    data->gun.arr[0]->enabled = 1;
    return (0);
}

void    reload(t_data *data)
{
    static int      i;
    static int      counter;

    if (!data->gun.nbr_sht && !counter)
    {
        ((i == 0) && (data->gun.arr[0]->enabled = 0));
        ((i) && (data->gun.arr[(i + 3)]->enabled = 0));
        i++;
        if (i == 8)
        {
            i = 0;
            data->gun.nbr_sht = 10;
            data->gun.arr[0]->enabled = 1;
        }
        else
            data->gun.arr[(i + 3)]->enabled = 1;
        counter = 2;
    }
    counter--;
}

void    shut(t_data *data)
{
    if (data && (data->gun.sht == 'S'))
    {
        if (data->gun.nbr_sht == 0)
            reload(data);
        else
        {
            data->gun.arr[data->gun.i]->enabled = 0;
            data->gun.i++;
            if (data->gun.i == 4)
            {
                data->gun.i = 0;
                data->gun.nbr_sht--;
                data->gun.sht = 'N';
                data->gun.arr[0]->enabled = 1;
            }
            else
                data->gun.arr[data->gun.i]->enabled = 1;
        }
    }
}
