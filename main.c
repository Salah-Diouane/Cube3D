# include "cube.h"

static int  ft_draw_cercle(mlx_image_t *img, double i, double j)
{
    double      x;
    double      y;
    double      incr;
    double      angle;
    int         raduis;

    raduis = -1;
    incr = ((2 * M_PI) / 360);
    while (++raduis < 3)
    {
        angle = 0;
        while (angle < (2 * M_PI))
        {
            x = i + (raduis * cos(angle));
            y = j + (raduis * sin(angle));
            mlx_put_pixel(img, x, y, 0x0000ffff);
            angle += incr;
        }
    }
    return (0);
}

void    ft_fill_img(t_data *data, mlx_image_t *img)
{
    int     i;
    int     j;

    j = 0;
    i = -1;
    while ((++i < img->width) && (j < img->height))
    {
        mlx_put_pixel(img, i, j, 0xffffff70);
        if ((i + 1) == img->width)
            (i = -1, j++);
    }
    ft_draw_cercle(data->wall_img, (data->wall_img->width / 2), \
        (data->wall_img->height / 2));
}

int ft_create_window(t_data  *data)
{
    if (!(data->mlx = mlx_init(data->wnd_wd, data->wnd_ht, \
        "cube", 0)))
        return (printf("data->mlx fails!!\n"));
    if (!(data->wall_img = mlx_new_image(data->mlx, 120, 120)))
        return (printf("data->wall_img fails!!\n"));
    if (!(data->rays_img = mlx_new_image(data->mlx, 120, 120)))
        return (printf("data->rays_img fails!!\n"));
    if (!(data->ddd__img = mlx_new_image(data->mlx, \
        data->wnd_wd, data->wnd_ht)))
        return (printf("data->ddd__img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->ddd__img, 0, 0))
        return (printf("data->ddd__img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->wall_img, 0, 0))
        return (printf("data->wall__img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->rays_img, 0, 0))
        return (printf("data.rays_img fails!!\n"));
    ft_fill_img(data, data->wall_img);
    return (0);
}

int main()
{
    t_data  data;
    char    *map = "1111111111 1000000001 1000010101 \
                    1100000001 1010110101 1010000001 \
                    1000000011 1010110001 1000000001 \
                    1000000011 1010110001 1000000001 \
                    1000000011 1010110001 1000000001 \
                    1000000011 1010110001 1000000001 \
                    1000000011 1010110001 1000000001 \
                    1111111111";

    data.plr.d = 0;
    data.plr.x = 30;
    data.plr.y = 30;
    data.grd_ht = 20;
    data.grd_wd = 20;
    data.wnd_ht = 700;
    data.wnd_wd = 1100;
    data.map = ft_split(map, ' ');
    if (!data.map)
        return (printf("ft_split fails!!\n"));
    data.array = (t_point *)malloc(sizeof(t_point) * data.wnd_wd);
    if (!data.array)
        return (printf("arr allocation!!\n"));
    if (ft_create_window(&data))
        return (-1);
    data.wall =  mlx_load_png("wood.png");
    data.img = mlx_texture_to_image(data.mlx, data.wall);
    ft_set_img(&data);
    mlx_loop_hook(data.mlx, ft_update, &data);
    ft_mini_map(&data);
    mlx_loop(data.mlx);
}    
