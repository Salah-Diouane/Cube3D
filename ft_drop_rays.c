# include "cube.h"

double  real_angle(double angle)
{
    double      two_pi;

    two_pi = 2 * M_PI;
    if (angle < 0)
        angle += two_pi;
    else if (two_pi <= angle)
        angle -= two_pi;
    return (angle);
}

static int  steps(t_data *data, t_point *inter, t_point *incr)
{
    double       d_x;
    double       d_y;
    double       steps;

    d_x = inter->x - data->plr.x;
    d_y = inter->y - data->plr.y;
    steps = fabs(d_x);
    if (fabs(d_x) < fabs(d_y))
        steps = fabs(d_y);
    incr->x = d_x / steps;
    incr->y = d_y / steps;
    return (steps);
}

static int ft_draw_line(t_data *data, t_point *inter)
{
    int         i;
    int         end;
    double      adja;
    double      oppo;
    t_point     incr;
    t_point     start;

    i = -1;
    start.x = 60;
    start.y = 60;
    end = steps(data, inter, &incr);
    while (++i < end)
    {
        mlx_put_pixel(data->rays_img, start.x, \
            start.y, 0xffff00aa);
        start.x += incr.x;
        start.y += incr.y;
        if ((start.x < 0) || (119 < start.x) || \
            (start.y < 0) || (119 < start.y))
            break ;
    }
    return (0);
}

void    ft_cast_rays(t_data *data)
{
    int      x;
    double   rad;
    double   dst;
    double   incr;
    double   angle;
    t_point  inter;

    x = data->wnd_wd;
    rad = (M_PI / 180);
    incr = ((60 * rad) / data->wnd_wd);
    angle = real_angle(data->plr.d - \
        (30 * rad));
    ft_mini_map(data);
    while (x--)
    {
        angle = real_angle(angle);
        dst = ft_get_inter(data, &inter, angle);
        data->array[x].x = inter.x;
        data->array[x].y = inter.y;
        if (x % 10 == 0)
            ft_draw_line(data, &inter);
        angle += incr;
    }
    ft_create_list(data);
    ft_render_wall(data);
}
