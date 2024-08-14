# include "manda.h"

int ft_create_window(t_data  *data)
{
    if (!(data->mlx = mlx_init(data->wnd_wd, data->wnd_ht, \
        "cube", 0)))
        return (put_error(data, "init mlx fails!!\n", 3));
    if (!(data->map.arr_img = mlx_new_image(data->mlx, 120, 120)) || \
        (mlx_image_to_window(data->mlx, data->map.arr_img, \
        10, 10) == - 1))
    {
        mlx_terminate(data->mlx);
        return (put_error(data, "init map_img fails!!\n", 3));
    }        
    if (!(data->proj_img = mlx_new_image(data->mlx, data->wnd_wd, \
        data->wnd_ht)) ||(mlx_image_to_window(data->mlx, \
        data->proj_img, 0, 0) == -1))
    {
        mlx_delete_image(data->mlx, data->map.arr_img);
        mlx_terminate(data->mlx);
        return (put_error(data, "init proj_img fails!!\n", 3));
    }
    if (init_gun(data))
    {
        mlx_terminate(data->mlx);
        return (put_error(data, "init gun fails!!", 3));
    }
    return (0);
}

int main()
{
    t_data  data;
    char    *map = "1111111111 1000000001 1000010101 \
                    1100000001 10101d11d1 1010000001 \
                    1000000011 1011d10001 1000000001 \
                    1111111111";

    data.fact = 4.0;
    data.plr.d = 0;
    data.plr.x = 370;
    data.plr.y = 370;
    data.grd_ht = 64;
    data.grd_wd = 64;
    data.wnd_ht = 700;
    data.wnd_wd = 1100;
    data.doors_nbr = 3;
    data.face_lst = NULL;
    data.plr.h = data.wnd_ht / 2;
    data.map = ft_split(map, ' ');
    if (!data.map)
        return (printf("ft_split fails!!\n"));
    data.inter_arr = malloc(sizeof(t_point) * data.wnd_wd);
    if (!data.inter_arr)
        return (put_error(&data, "inter_arr allocation fails!!\n", 1));
    data.door_arr = malloc(sizeof(t_door) * data.doors_nbr);
    if (!data.door_arr)
        return (put_error(&data, "door_arr allocation fails!!\n", 2));
    fill_door_array(&data);
    if (ft_create_window(&data))
        return (-1);
    data.D_texture = get_texture_arr(&data, "door.png");
    data.W_texture = get_texture_arr(&data, "wall.png");
    ft_mini_map(&data);
    mlx_loop_hook(data.mlx, animation, &data);
    mlx_loop(data.mlx);
    return (0);
}