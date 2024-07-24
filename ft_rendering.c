# include "cube.h"

static double ft_real_angle(double angle)
{
    if (angle < 0)
        angle += (2 * M_PI);
    else if ((2 * M_PI) <= angle)
        angle -= (2 * M_PI);
    return (angle);
}

static double get_height(t_data *data, int i)
{
    double      oppo;
    double      adja;
    double      pro_plan;
    double      result;

    adja = fabs(data->plr->x - data->array[i].x);
    oppo = fabs(data->plr->y - data->array[i].y);
    pro_plan = 760 / (2 * tan(30 * (M_PI / 180)));
    result = ((10 * pro_plan) / sqrt((oppo * oppo) + \
        (adja * adja)));
    return (result);
}

void    ft_render_wall(t_data *data)
{
    double      y;
    double      x;
    t_face      *tmp;
    int         i;
    double      step;

    x = 0;
    tmp = data->face_lst;
    while (tmp)
    {
        i = 0;
        step = (tmp->height_2 - tmp->height_1) / tmp->rays;
        while (i < tmp->rays)
        {
            y = (data->wd_ht / 2) - (tmp->height_1 / 2);
            while (y < ((data->wd_ht / 2) + (tmp->height_1 / 2)))
            {
                if (0 < y && y < data->wd_ht)
                    mlx_put_pixel(data->ddd__img, \
                        x, y, 0xffffffff);
                y++;
            }
            i++;
            x++;
            tmp->height_1 += step;
        }
        tmp = tmp->next;
    }
}
