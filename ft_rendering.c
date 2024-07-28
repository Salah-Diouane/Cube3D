# include "cube.h"

static void set_direction_and_offset(t_data *data, t_face *tmp, double x,
    int *off_x)
{
    if (tmp->fix == 1)
    {
        if (data->array[(int)x].x > data->plr.x)
            (1) && (data->face_lst->dir = 's',
                *off_x = (int)((int)data->array[(int)x].y % data->grd_ht));
        else
            (1) && (data->face_lst->dir = 'n', 
                *off_x = (int)((int)data->array[(int)x].y % data->grd_ht));
    }
    else if (tmp->fix == 2)
    {
        if (data->array[(int)x].y > data->plr.y)
            (1) && (data->face_lst->dir = 'e',
                *off_x = (int)((int)data->array[(int)x].x % data->grd_wd));
        else
            (1) && (data->face_lst->dir = 'w',
                *off_x = (int)((int)data->array[(int)x].x % data->grd_wd));
    }
}


static void render_pixel(t_data *data, double x, double y, int off_x, int off_y)
{
    if (data->face_lst->dir == 's')
        mlx_put_pixel(data->ddd__img, x, y,
            data->texture_s[(data->grd_wd * off_y) + off_x]);
    else if (data->face_lst->dir == 'n')
        mlx_put_pixel(data->ddd__img, x, y,
            data->texture_n[(data->grd_wd * off_y) + off_x]);
    else if (data->face_lst->dir == 'e')
        mlx_put_pixel(data->ddd__img, x, y,
            data->texture_e[(data->grd_wd * off_y) + off_x]);
    else if (data->face_lst->dir == 'w')
        mlx_put_pixel(data->ddd__img, x, y,
            data->texture_w[(data->grd_wd * off_y) + off_x]);
}

static int ft_render_line(t_data *data, t_face *tmp, double ht, double x)
{
    double  y;
    double  top;
    int     off_x;
    int     off_y;

    y = (data->wnd_ht / 2) - (ht / 2);
    set_direction_and_offset(data, tmp, x, &off_x);
    top = y;
    while (y < ((data->wnd_ht / 2) + (ht / 2)))
    {
        off_y = (y - top) * (128 / ht);
        if (0 <= y && y < data->wnd_ht)
            render_pixel(data, x, y, off_x, off_y);
        y = y + 1;
    }
    return (0);
}

static void ft_put_pixels(t_data *data, mlx_image_t *img)
{
    int         i;
    int         j;

    j = img->height / 2;
    while (j < img->height)
    {
        i = 0;
        while (i < img->width)
        {
            mlx_put_pixel(img, i, j, 0x228B22);
            i++;
        }
        j++;
    }
}

void ft_render_wall(t_data *data)
{
    int         i;
    double      x;
    t_face      *tmp;
    double      step;
    mlx_image_t *img;
    
    img = data->ddd__img;
    ft_put_pixels(data, img);
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
