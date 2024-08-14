# include "../include/bonus.h"
# include "../include/bonus_parser.h"

static int  initiate_vars(t_data *data)
{
    data->fact = 4.0;
    data->wnd_ht = 700;
    data->wnd_wd = 1100;
    data->face_lst = NULL;
    data->plr.h = data->wnd_ht / 2;
    data->grd_ht = data->grd_wd = 64;
    data->door_text.path = "door.png";
    if (!(data->inter_arr = malloc(sizeof(t_point) *  \
        data->wnd_wd)))
        return (put_error(data, "inter_arr allocation fails!!\n", 1));
    data->door_arr = malloc(sizeof(t_door) * data->doors_nbr);
    if (!data->door_arr)
        return (put_error(NULL, "door_arr allocation fails!!\n", 2));
    return (0);
}

static int  load_textures(t_data *data)
{
    if (!(data->north_text.arr = get_texture_arr(data, \
        data->north_text.path)))
        return (-1);
    if (!(data->south_text.arr = get_texture_arr(data, \
        data->south_text.path)))
        return (free_textures(data, 1), -1);
    if (!(data->west_text.arr = get_texture_arr(data, \
        data->west_text.path)))
        return (free_textures(data, 2), -1);   
    if (!(data->east_text.arr = get_texture_arr(data, \
        data->east_text.path)))
        return (free_textures(data, 3), -1);
    if (!(data->door_text.arr = get_texture_arr(data, \
        data->door_text.path)))
        return (free_textures(data, 4), -1);
    return (0);
}

int ft_create_window(t_data  *data)
{
    if (!(data->mlx = mlx_init(data->wnd_wd, data->wnd_ht, \
        "cube", 0)))
        return (put_error(data, "init mlx fails!!\n", 3));
    if (!(data->proj_img = mlx_new_image(data->mlx, data->wnd_wd, \
        data->wnd_ht)) ||(mlx_image_to_window(data->mlx, \
        data->proj_img, 0, 0) == -1))
    {
        mlx_terminate(data->mlx);
        return (put_error(data, "init proj_img fails!!\n", 3));
    }
    if (!(data->map_img = mlx_new_image(data->mlx, 120, 120)) || \
        (mlx_image_to_window(data->mlx, data->map_img, \
        10, 10) == - 1))
    {
        mlx_delete_image(data->mlx, data->proj_img);
        mlx_terminate(data->mlx);
        return (put_error(data, "init map_img fails!!\n", 3));
    }        
    if (init_gun(data))
    {
        mlx_terminate(data->mlx);
        return (put_error(data, "init gun fails!!", 3));
    }
    return (0);
}

int main(int ac, char **av)
{
    t_data  data;

    if (ft_parsing(&data, av))
        return (0);
    if (initiate_vars(&data))
        return (0);
    fill_door_array(&data);
    if (ft_create_window(&data))
        return (0);
    ft_mini_map(&data);
    load_textures(&data);
    mlx_loop_hook(data.mlx, animation, &data);
    mlx_loop(data.mlx);
    return (0);
}