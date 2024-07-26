# include "cube.h"

void    ft_fill_img(mlx_image_t *img)
{
    int     i;
    int     j;

    j = 0;
    i = -1;
    while ((++i < img->width) && (j < img->height))
    {
        mlx_put_pixel(img, i, j, 0xff00000f);
        if ((i + 1) == img->width)
            (i = -1, j++);
    }
}

static int ft_mini_map(t_data *data)
{
    int     i;
    int     j;

    j = 0; 
    i = -1;
    while (data->map[j][++i])
    {
        if (data->map[j][i] == '1')
            mlx_image_to_window(data->mlx, \
                data->wall_img, (i * data->tl_wd), \
                (j * data->tl_ht));
        if (!data->map[j][(i + 1)])
            (i = -1, j++);
    }
    return (0);
}

int ft_create_window(t_data  *data)
{
    if (!(data->mlx = mlx_init(data->wd_wh, data->wd_ht, \
        "cube", 0)))
        return (printf("data->mlx fails!!\n"));
    if (!(data->wall_img = mlx_new_image(data->mlx, \
        data->tl_wd, data->tl_ht)))
        return (printf("data->wall_img fails!!\n"));
    if (!(data->rays_img = mlx_new_image(data->mlx, \
        (data->tl_wd * 10), (data->tl_ht * 10))))
        return (printf("data->rays_img fails!!\n"));
    if (!(data->ddd__img = mlx_new_image(data->mlx, \
        data->wd_wh, data->wd_ht)))
        return (printf("data->ddd__img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->ddd__img, 0, 0))
        return (printf("data->ddd__img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->rays_img, 0, 0))
        return (printf("data.rays_img fails!!\n"));
    ft_fill_img(data->wall_img);
    return (0);
}

int32_t *ft_get_img()
{
    int32_t *txt;
    int     i;
    int     j;

    i = 0;
    txt = (int32_t *)malloc(sizeof(int32_t) * 200);
    if(!txt)
        return (NULL);
    while (i < 20)
    {
        j = 0;
        while (j < 20)
        {
            if ((i % 2 == 0) || (j % 2 == 0))
                txt[i] = 0x005050FF;
            else
                txt[i] = 0x00A0A0FF;
            j++;
        }
        i++;
    }
    return (txt);
}

int main()
{
    t_plr   plr;
    char    *map = "1111111111 1000000001 1000010101 \
                    1110000001 1010110101 1010000001 \
                    1000000011 1010110001 1000000001 \
                    1111111111";
    t_data  data;

    plr.d = 0;
    plr.x = 30;
    plr.y = 30;
    data.tl_ht = 20;
    data.tl_wd = 20;
    data.wd_ht = 700;
    data.wd_wh = 760;
    data.plr = &plr;
    data.map = ft_split(map, ' ');
    data.texture = ft_get_img();
    // data.texture = mlx_load_xpm42("wall.xpm");
    if (!data.map)
        return (printf("ft_split fails!!\n"));
    data.array = (t_point *)malloc(sizeof(t_point) * data.wd_wh);
    if (!data.array)
        return (printf("arr allocation!!\n"));
    if (ft_create_window(&data))
        return (-1);
    mlx_key_hook(data.mlx, ft_move_plr, &data);
    // ft_mini_map(&data);
    mlx_loop(data.mlx);
    return (0);
}
