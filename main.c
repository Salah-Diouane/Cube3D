# include "cube.h"

void    ft_fill_img(mlx_image_t *img)
{
    int     i;
    int     j;

    j = -1;
    while (++j < img->height)
    {
        i = -1;
        while (++i < img->width)
            mlx_put_pixel(img, i, j, 0xff0000ff);
    }

}

static int ft_mini_map(t_data *data)
{
    int     i;
    int     j;

    j = -1;
    while (data->map[++j])
    {
        i = -1;
        while (data->map[j][++i])
        {
            if (data->map[j][i] == '1')
                mlx_image_to_window(data->mlx, \
                    data->wall_img, (i * data->tl_wd), \
                    (j * data->tl_ht));

        }
    }
    return (0);
}

int main()
{
    t_plr   plr;
    char    *map = "1111111111 1000000001 1000011101 \
                    1110000001 1010111101 1010000001 \
                    1000000011 1011110001 1000000001 \
                    1111111111";
    t_data  data;

    plr.d = 0;
    plr.x = 30;
    plr.y = 30;
    data.tl_ht = 20;
    data.tl_wd = 20;
    data.wd_ht = 700;
    data.wd_wd = 760;
    data.plr = &plr;
    data.map = ft_split(map, ' ');
    // data.map = read_map();
    if (!data.map)
        return (printf("ft_split fails!!\n"));
    data.mlx = mlx_init(data.wd_wd, data.wd_ht, "cube", 0);
    data.wall_img = mlx_new_image(data.mlx, \
    data.tl_wd, data.tl_ht);
    data.rays_img = mlx_new_image(data.mlx, \
        (data.tl_wd * 10), (data.tl_ht * 10));
    data.ddd__img = mlx_new_image(data.mlx, \
        data.wd_wd, data.wd_ht);
    mlx_image_to_window(data.mlx, data.ddd__img, 0, 0);
    mlx_image_to_window(data.mlx, data.rays_img, 0, 0);
    ft_fill_img(data.wall_img);
    mlx_key_hook(data.mlx, ft_move_plr, &data);
    ft_mini_map(&data);
    mlx_loop(data.mlx);
    return (0);
}
