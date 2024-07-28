# include "cube.h"

// static int ft_render_line(t_data *data, t_face *tmp, double ht, double x)
// {
//     double  y;
//     double  top;
//     int     off_x;
//     int     off_y;
//     int     width = data->img->width;
//     int     height = data->img->height;

//     y = (data->wd_ht / 2) - (ht / 2);
//     if (tmp->fix == 1)
//     {
//         if (data->array[(int)x].x > data->plr->x)
//         {
//             data->face_lst->dir = 's';
//             off_x = (int)((int)data->array[(int)x].y % data->tl_ht);
//         }
//         else
//         {
//             data->face_lst->dir = 'n';
//             off_x = (int)((int)data->array[(int)x].y % data->tl_ht);
//         }
//     }
//     else if (tmp->fix == 2)
//     {
//         if (data->array[(int)x].y > data->plr->y)
//         {
//             data->face_lst->dir = 'e';
//             off_x = (int)((int)data->array[(int)x].x % data->tl_wd);
//         }
//         else
//         {
//             data->face_lst->dir = 'w';
//             off_x = (int)((int)data->array[(int)x].x % data->tl_wd);
//         }
//     }
//     top = y;
//     while (y < ((data->wd_ht / 2) + (ht / 2)))
//     {
//         off_y = (y - top) * (20 / ht);
//         if (0 <= y && y < height && 0 <= x && x < width)
//         {
            // if (data->face_lst->dir == 's')
            //     mlx_put_pixel(data->img, x, y, data->texture_s[(data->tl_wd * off_y) + off_x]);
            // else if (data->face_lst->dir == 'n')
            //     mlx_put_pixel(data->ddd__img, x, y, data->texture_n[(data->tl_wd * off_y) + off_x]);
            // else if (data->face_lst->dir == 'e')
            //     mlx_put_pixel(data->ddd__img, x, y, data->texture_e[(data->tl_wd * off_y) + off_x]);
            // else if (data->face_lst->dir == 'w')
            //     mlx_put_pixel(data->ddd__img, x, y, data->texture_w[(data->tl_wd * off_y) + off_x]);
//         }
//         y++;
//     }
//     return (0);
// }

static int ft_render_line(t_data *data, t_face *tmp, double ht, double x)
{
    double  y;
    double  top;
    int     off_x;
    int     off_y;
    int     width = data->img->width;
    int     height = data->img->height;

    y = (data->wnd_ht / 2) - (ht / 2);
    if (tmp->fix == 1)
    {
        if (data->array[(int)x].x > data->plr.x)
        {
            data->face_lst->dir = 's';
            off_x = (int)((int)data->array[(int)x].y % data->grd_ht);
        }
        else
        {
            data->face_lst->dir = 'n';
            off_x = (int)((int)data->array[(int)x].y % data->grd_ht);
        }
    }
    else if (tmp->fix == 2)
    {
        if (data->array[(int)x].y > data->plr.y)
        {
            data->face_lst->dir = 'e';
            off_x = (int)((int)data->array[(int)x].x % data->grd_wd);
        }
        else
        {
            data->face_lst->dir = 'w';
            off_x = (int)((int)data->array[(int)x].x % data->grd_wd);
        }
    }
    top = y;
    while (y < ((data->wnd_ht / 2) + (tmp->height_1 / 2)))
    {
        off_y = (int)((y - top) * \
            (data->grd_ht / tmp->height_1));
        if (0 < y && y < data->wnd_ht)
            mlx_put_pixel(data->ddd__img, \
                x, y, data->texture_e[(data->grd_wd * \
                    off_y) + off_x]);
        y++;
    }
    // while (y < ((data->wd_ht / 2) + (ht / 2)))
    // {
    //     off_y = (y - top) * (20 / ht);
    //     if (0 <= y && y < data->img->height)
    //     {
    //         if (data->face_lst->dir == 's')
    //             mlx_put_pixel(data->img, x, y, data->texture_s[(data->tl_wd * off_y) + off_x]);
    //         else if (data->face_lst->dir == 'n')
    //             mlx_put_pixel(data->ddd__img, x, y, data->texture_n[(data->tl_wd * off_y) + off_x]);
    //         else if (data->face_lst->dir == 'e')
    //             mlx_put_pixel(data->ddd__img, x, y, data->texture_e[(data->tl_wd * off_y) + off_x]);
    //         else if (data->face_lst->dir == 'w')
    //             mlx_put_pixel(data->ddd__img, x, y, data->texture_w[(data->tl_wd * off_y) + off_x]);
    //     }
    //     y = y + 1;
    // }
    return (0);
}

void ft_render_wall(t_data *data)
{
    int         i;
    int         j;
    double      x;
    t_face      *tmp;
    double      step;
    mlx_image_t *img;
    
    img = data->ddd__img;
    j = 0;
    // while (j < img->height / 2)
    // {
    //     i = 0;
    //     while (i < img->width)
    //     {
    //         mlx_put_pixel(img, i, j, 0x87CEEB);
    //         i++;
    //     }
    //     j++;
    // }
    // j = img->height / 2;
    // while (j < img->height)
    // {
    //     i = 0;
    //     while (i < img->width)
    //     {
    //         mlx_put_pixel(img, i, j, 0x228B22);
    //         i++;
    //     }
    //     j++;
    // }
    x = 0;
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

