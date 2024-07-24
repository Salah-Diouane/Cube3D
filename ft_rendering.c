# include "cube.h"

static int  ft_render_line(t_data *data, double ht, double x)
{
    double      y;

    y = (data->wd_ht / 2) - (ht / 2);
    while (y < ((data->wd_ht / 2) + (ht / 2)))
    {
        if (0 < y && y < data->wd_ht)
            mlx_put_pixel(data->ddd__img, \
                x, y, 0xffffffff);
        y++;
    }
    return (0);
}

void    ft_render_wall(t_data *data)
{
    int         i;
    double      x;
    t_face      *tmp;
    double      step;

    x = 0, 
    tmp = data->face_lst;
    while (tmp)
    {
        i = -1;
        step = (tmp->height_2 - tmp->height_1) / tmp->rays;
        while (++i < tmp->rays)
        {
            ft_render_line(data, tmp->height_1, x);
            tmp->height_1 += step;
            x++;
        }
        tmp = tmp->next;
    }
}
