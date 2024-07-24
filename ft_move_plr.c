# include "cube.h"

// void    ft_clear_image(mlx_image_t *img)
// {
//     int     i;
//     int     j;

//     j = -1;
//     while (++j < img->height)
//     {
//         i = -1;
//         while (++i < img->width)
//             mlx_put_pixel(img, i, j, 0x00);
//     }
// }

// mlx_keyfunc ft_move_plr(mlx_key_data_t key, t_data *data)
// {
//     if (key.key == 65)
//         data->plr->x -= 3;
//     else if (key.key == 68)
//         data->plr->x += 3;
//     else if (key.key == 83)
//         data->plr->y += 3;
//     else if (key.key == 87)
//         data->plr->y -= 3;
//     else if (key.key == 262)
//     {
//         data->plr->d -= 5;
//         if (data->plr->d < 0)
//             data->plr->d += 360;
//     }
//     else if (key.key == 263)
//     {
//         data->plr->d += 5;
//         data->plr->d %= 360;
//     }
//     ft_clear_image(data->rays_img);
//     ft_clear_image(data->ddd__img);
//     ft_drop_rays(data);
//     return (0);
// }

void    ft_clear_image(mlx_image_t *img)
{
    int     i;
    int     j;

    j = -1;
    while (++j < img->height)
    {
        i = -1;
        while (++i < img->width)
            mlx_put_pixel(img, i, j, 0x00);
    }
}

static int  ft_check_next(t_data *data, double x, double y)
{
    if ((data->map[(int)((y + 3) / 20)][(int)(x / 20)] == '1') || \
        (data->map[(int)((y - 3) / 20)][(int)(x / 20)] == '1') || \
        (data->map[(int)(y / 20)][(int)((x + 3) / 20)] == '1') || \
        (data->map[(int)(y / 20)][(int)((x - 3) / 20)] == '1'))
        return (1);
    return (0);
}

static void ft_for_back_ward(t_data *data, int keycode)
{
    double      x;
    double      y;
    double      angle;

    if (keycode == 87)
    {
        angle = (double)(data->plr->d * (M_PI / 180));
        x = data->plr->x + (3 * cos(angle));
        y = data->plr->y + (3 * sin(angle) * -1);
    }
    else if (keycode == 83)
    {
        angle = (double)((data->plr->d + 180) * (M_PI / 180));
        x = data->plr->x + (3 * cos(angle));
        y = data->plr->y + (3 * sin(angle) * -1);
    }
    if (!ft_check_next(data, x, y))
        (data->plr->x = x, data->plr->y = y);
}

static void ft_go_left_right(t_data *data, int keycode)
{
    double      x;
    double      y;
    double       angle;

    if (keycode == 65)
    {
        angle = (double)((data->plr->d + 90) * (M_PI / 180));
        x = data->plr->x + (3 * cos(angle));
        y = data->plr->y + (3 * sin(angle) * -1);
    }
    else if (keycode == 68)
    {
        angle = (double)((data->plr->d + 270) * (M_PI / 180));
        x = data->plr->x + (3 * cos(angle));
        y = data->plr->y + (3 * sin(angle) * -1);
    }
    if (!ft_check_next(data, x, y))
        (data->plr->x = x, data->plr->y = y);
}

mlx_keyfunc ft_move_plr(mlx_key_data_t key, t_data *data)
{
    if (key.key == 65 || key.key == 68)
        ft_go_left_right(data, key.key);
    else if ((key.key == 83) || (key.key == 87))
        ft_for_back_ward(data, key.key);
    else if (key.key == 262)
    {
        data->plr->d -= 5;
        if (data->plr->d < 0)
            data->plr->d += 360;
    }
    else if (key.key == 263)
    {
        data->plr->d += 5;
        data->plr->d %= 360;
    }
    ft_clear_image(data->rays_img);
    ft_clear_image(data->ddd__img);
    ft_drop_rays(data);
    return (0);
}
