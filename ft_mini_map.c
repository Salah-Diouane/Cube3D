# include "cube.h"


int ft_mini_map(t_data *data)
{
    int     i;
    int     j;
    int     i_ref;
    int     j_ref;

    j_ref = (int)((data->plr.y / 8) - 60);
    i_ref = (int)((data->plr.x / 8) - 60);
    j = j_ref;
    i = i_ref - 1;
    while (j < (int)((data->plr.y / 8) + 60))
    {
        i++;
        if ((0 < j) && (j < ((data->grd_ht / 8) * 10)) && \
            (0 < i) && (i < ((data->grd_wd / 8) * 10)) && \
            (data->s_map->map[(int)(j / (data->grd_ht / 8))][(int)(i / \
            (data->grd_wd / 8))] == '1'))
            mlx_put_pixel(data->rays_img, (i - i_ref), (j - \
                j_ref), 0xff0000f0);
        if ((int)((data->plr.x / 8) + 60) <= i)
            (i = i_ref - 1, j++);
    }
    return (0);
}
