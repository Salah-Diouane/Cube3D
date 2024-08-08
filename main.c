# include "cube.h"

int32_t *get_texture(int width, int height, int32_t color)
{
    int         i;
    int         j;
    int32_t     *texture;

    j = -1;
    texture = (int32_t *)malloc(sizeof(int32_t) * \
        (width * height));
    if (!texture)
        return (NULL);
    while (++j < height)
    {
        i = -1;
        while (++i < width)
        {
            if ((i % 16 == 0) || (j % 16 == 0))
                texture[(j * width) + i] = 0x000000ff;
            else
                texture[(j * width) + i] = color;
        }
    }
    return (texture);
}

int ft_create_window(t_data  *data)
{
    if (!(data->mlx = mlx_init(data->wnd_wd, data->wnd_ht, \
        "cube", 0)))
        return (printf("init mlx fails!!\n"));
    if (!(data->map_img = mlx_new_image(data->mlx, 120, 120)))
        return (printf("data->map_img fails!!\n"));
    if (!(data->proj_img = mlx_new_image(data->mlx, \
        data->wnd_wd, data->wnd_ht)))
        return (printf("data->proj_img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->proj_img, 0, 0))
        return (printf("data->proj_img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->map_img, 10, 10))
        return (printf("data->wall__img fails!!\n"));
    if (init_gun_arr(data))
        return (printf("init gun array fails!!"));
    return (0);
}

void fct()
{
    system("leaks cube");
}
// C                 5,11 segv
int main(int arc, char **arv)
{
    t_data  data;
    t_map *map;
    t_col *lst;

    atexit(fct);
    data.fact = 4.0;

    data.grd_ht = 64;
    data.grd_wd = 64;

    data.wnd_ht = 700;
    data.wnd_wd = 1100;
	map = (t_map *)malloc(sizeof(t_map));
	data.s_map = map;
	data.text = NULL;
	data.colors = NULL;

    data.face_lst = NULL;
    data.w_text.wd = 64;
    data.w_text.ht = 64;
    data.gun.i = 0;
    data.gun.sht = 'N';
    data.gun.nbr_sht = 10;
    data.plr.h = data.wnd_ht / 2;
    if (arc != 2)
        return (printf("number of args invalid !!!!"));
    if (ft_parsing(&data, arv) != 0)
    {
        if (data.s_map->map[0])
            ft_free_2d(data.s_map->map);
        free(map);
		return (printf("ft_parsing failed !!!!"));
    }
    // while (data.text)
    // {
    //     printf("iden : |%s|\n", data.colors->identif);
    //     printf("path : |%s|\n", data.text->chem);
    //     data.text = data.text->next;
    // }
    // while (data.colors)
    // {
    //     printf("iden : |%s|\n", data.colors->identif);
    //     printf("r : |%d|\tg : |%d|\tb : |%d|\n", data.colors->r, data.colors->g, data.colors->b);
    //     data.colors = data.colors->next;
    // }
    // int  i = 0;
    // while (data.s_map->map[i])
    // {
    //     printf("|%s|\n", data.s_map->map[i++]);
    // }

    // if (ft_create_window(&data))
    //     return (-1);
    // data.inter_arr = malloc(sizeof(t_point) * data.wnd_wd);
    // if (!data.inter_arr)
    //     return (printf("inter_arr allocation fails!!\n"));
    // data.door_arr = malloc(sizeof(t_door) * data.doors_nbr);
    // if (!data.door_arr)
    //     return (printf("door_arr allocation fails!!\n"));
	ft_set_img(&data);
    // fill_door_array(&data);
    // ft_mini_map(&data);
    // mlx_loop_hook(data.mlx, animation, &data);
    // mlx_loop(data.mlx);
    ft_free_2d(data.s_map->map);
    free(map);
    free_color(data.colors);
    free_texture(data.text);
    // return (0);
}
