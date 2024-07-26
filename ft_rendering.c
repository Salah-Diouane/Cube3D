# include "cube.h"

static int  ft_render_line(t_data *data, t_face *tmp, double ht, double x)
{
    double      y;
    double      top;
    int         off_x;
    int         off_y;

    if (tmp->fix == 1)
        off_x = (int)data->array[(int)x].x % 20;
    else
        off_x = (int)data->array[(int)x].y % 20;
    y = (data->wd_ht / 2) - (ht / 2); // pixel ofla
    top = y;
    while (y < ((data->wd_ht / 2) + (ht / 2)))
    {
        off_y = (y - top) * (20 / ht);
        if (0 < y && y < data->wd_ht)
            mlx_put_pixel(data->ddd__img, \
                x, y, data->texture[off_y + off_x]);
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
            ft_render_line(data, tmp, tmp->height_1, x);
            tmp->height_1 += step;
            x++;
        }
        tmp = tmp->next;
    }
}
