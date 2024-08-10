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

void    ft_cast_rays(t_data *data)
{
    int      x;
    double   rad;
    double   incr;
    double   angle;
    t_point  inter;

    if (data && data->s_map->map && data->inter_arr)
    {
        x = data->wnd_wd;
        rad = (M_PI / 180);
        incr = ((60 * rad) / data->wnd_wd);
        angle = real_angle(data->plr.d - (30 * rad));
        ft_mini_map(data);
        ft_free_lst(data->face_lst);
        while (x--)
        {
            angle = real_angle(angle);
            ft_inter(data, &inter, angle);
            data->inter_arr[x].x = inter.x;
            data->inter_arr[x].y = inter.y;
            angle += incr;
        }
        data->face_lst = face_list(data);
        ft_render_wall(data);
    }
}
