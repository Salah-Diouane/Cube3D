/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:53:44 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/13 21:10:35 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cube.h"
# include "../include/manda_parser.h"

static int  initiate_vars(t_data *data)
{
    data->wnd_ht = 700;
    data->wnd_wd = 1100;
    data->face_lst = NULL;
    data->grd_ht = data->grd_wd = 64;
    if (!(data->inter_arr = malloc(sizeof(t_point) *  data->wnd_wd)))
        return (put_error(data, "inter_arr allocation fails!!\n", 1));
    return (0);
}

static int  load_textures(t_data *data)
{
    if (!(data->north_text.arr = get_texture_arr(data, \
        data->north_text.path)))
        return (-1);
    if (!(data->south_text.arr = get_texture_arr(data, \
        data->south_text.path)))
        return (-1);
    if (!(data->west_text.arr = get_texture_arr(data, \
        data->west_text.path)))
        return (-1);   
    if (!(data->east_text.arr = get_texture_arr(data, \
        data->east_text.path)))
        return (-1);
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
    return (0);
}

int main(int ac, char **av)
{
    t_data  data;

    if (initiate_vars(&data))
        return (-1);
    if (ft_parsing(&data, av))
        return (-1);
    printf("north: %s\n", data.north_text.path);
    if (ft_create_window(&data))
        return (-1);
    if (load_textures(&data))
        return (-1);
    ft_cast_rays(&data);
    mlx_loop_hook(data.mlx, animate_plr, &data);
    mlx_loop(data.mlx);
    return (0);
}