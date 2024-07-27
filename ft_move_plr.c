#include "cube.h"

void ft_clear_image(mlx_image_t *img)
{
    int i;
    int j;

    j = -1;
    while (++j < img->height)
    {
        i = -1;
        while (++i < img->width)
            mlx_put_pixel(img, i, j, 0x00);
    }
}

static int ft_check_next(t_data *data, double x, double y)
{
    if ((data->map[(int)((y + 3) / 20)][(int)(x / 20)] == '1') ||
        (data->map[(int)((y - 3) / 20)][(int)(x / 20)] == '1') ||
        (data->map[(int)(y / 20)][(int)((x + 3) / 20)] == '1') ||
        (data->map[(int)(y / 20)][(int)((x - 3) / 20)] == '1'))
        return (1);
    return (0);
}

static void ft_for_back_ward(t_data *data, int keycode)
{
    double x;
    double y;

    if (keycode == 87)
    {
        x = data->plr->x + (4 * cos(data->plr->d));
        y = data->plr->y + (4 * sin(data->plr->d) * -1);
    }
    else if (keycode == 83)
    {
        x = data->plr->x + (4 * cos(data->plr->d) * -1);
        y = data->plr->y + (4 * sin(data->plr->d));
    }
    if (!ft_check_next(data, x, y))
        (data->plr->x = x, data->plr->y = y);
}

static void ft_go_left_right(t_data *data, int keycode)
{
    double x;
    double y;
    double angle;

    if (keycode == 65)
    {
        angle = real_angle(data->plr->d + (M_PI / 2));
        x = data->plr->x + (double)(4 * cos(angle));
        y = data->plr->y + (double)(4 * sin(angle) * -1);
    }
    else if (keycode == 68)
    {
        angle = real_angle(data->plr->d + (M_PI + (M_PI / 2)));
        x = data->plr->x + (double)(4 * cos(angle));
        y = data->plr->y + (double)(4 * sin(angle) * -1);
    }
    if (!ft_check_next(data, x, y))
        (data->plr->x = x, data->plr->y = y);
}

void ft_update(t_data *data)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        ft_for_back_ward(data, 87);
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        ft_for_back_ward(data, 83);
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        ft_go_left_right(data, 65);
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        ft_go_left_right(data, 68);
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        data->plr->d = real_angle(data->plr->d - (double)(5 * (M_PI / 180)));
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        data->plr->d = real_angle(data->plr->d + (double)(5 * (M_PI / 180)));
    ft_clear_image(data->rays_img);
    ft_clear_image(data->ddd__img);
    ft_drop_rays(data);
}
