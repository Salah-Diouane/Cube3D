# include "cube.h"
static int ft_render_line(t_data *data, t_face *tmp, double ht, double x)
{
    double  y;
    double  top;
    int     off_x;
    int     off_y;

    y = (data->wd_ht / 2) - (ht / 2);
    if (tmp->fix == 1)
    {
        if (data->array[(int)x].x > data->plr->x)
        {
            data->face_lst->dir = 's';
            off_x = (int)data->array[(int)x].x % 20;
        }
        else
        {
            data->face_lst->dir = 'n';
            off_x = (int)data->array[(int)x].x % 20;
        }
    }
    else if (tmp->fix == 2)
    {
        if (data->array[(int)x].y > data->plr->y)
        {
            data->face_lst->dir = 'e';
            off_x = (int)data->array[(int)x].y % 20;
        }
        else
        {
            data->face_lst->dir = 'w';
            off_x = (int)data->array[(int)x].y % 20;
        }
    }
    top = y;
    while (y < ((data->wd_ht / 2) + (ht / 2)))
    {
        off_y = (y - top) * (20 / ht);
        if (0 < y && y < data->wd_ht)
        {
            if (data->face_lst->dir == 's')
                mlx_put_pixel(data->ddd__img, x, y, data->texture_s[off_y + off_x]);
            else if (data->face_lst->dir == 'n')
                mlx_put_pixel(data->ddd__img, x, y, data->texture_n[off_y + off_x]);
            else if (data->face_lst->dir == 'e')
                mlx_put_pixel(data->ddd__img, x, y, data->texture_e[off_y + off_x]);
            else if (data->face_lst->dir == 'w')
                mlx_put_pixel(data->ddd__img, x, y, data->texture_w[off_y + off_x]);
        }
        y++;
    }
    return (0);
}



void ft_render_wall(t_data *data)
{
    int i;
    double x;
    t_face *tmp;
    double step;

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