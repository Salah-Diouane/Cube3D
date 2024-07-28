# include "cube.h"


int ft_mini_map(t_data *data)
{
    int     i;
    int     j;
    int     i_ref;
    int     j_ref;

    j_ref = (int)(data->plr.y - 60);
    i_ref = (int)(data->plr.x - 60);
    j = j_ref;
    i = i_ref - 1;
    while (j < (int)(data->plr.y + 60))
    {
        i++;
        if ((0 < j) && (j < (data->grd_ht * 22)) && \
            (0 < i) && (i < (data->grd_wd * 10)) && \
            (data->map[(int)(j / data->grd_ht)][(int)(i / \
            data->grd_wd)] == '1'))
            mlx_put_pixel(data->rays_img, i - i_ref, j - \
                j_ref, 0xff0000aa);
        if ((int)(data->plr.x + 60) <= i)
            (i = i_ref - 1, j++);
    }
    return (0);
}