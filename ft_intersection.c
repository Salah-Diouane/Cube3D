# include "cube.h"

static int  ft_is_wall(t_data *data, t_point *point, int x_d, int y_d)
{
    int         tl_ht;
    int         tl_wd;
    char        **map;

    map = data->map;
    tl_ht = data->tl_ht;
    tl_wd = data->tl_wd;
    if ((point->x < 0) || (point->y < 0) || \
        ((data->tl_wd * 10) < point->x) || \
        ((data->tl_ht * 10) < point->y))
        return (0);
    else if (map[(int)((point->y / tl_ht) - \
        (1 * (y_d < 0)))][(int)((point->x / \
            tl_wd) - (1 * (x_d < 0)))] == '1')
        return (1);
    return (0);
}

static double ft_hor_inter(t_data *data, t_point *inter, double angle)
{
    int         x_dir;
    int         y_dir;
    int         tl_ht;
    double      adja;
    double      oppo;

    tl_ht = data->tl_ht;
    inter->y = (data->plr->y / tl_ht) * tl_ht;
    x_dir = 1 - (2 * ((M_PI / 2) < angle && \
        angle < (M_PI + (M_PI / 2))));
    y_dir = 1 - (2 * (0 < angle && angle < M_PI));
    while ((0 < inter->y) && (inter->y < \
        (data->tl_ht * 20)))
    {
        if (((0 < y_dir) && (data->plr->y < inter->y)) || \
            ((y_dir < 0) && (inter->y < data->plr->y)))
        {
            oppo = fabs(data->plr->y - inter->y);
            adja = fabs(oppo / tan(angle));
            inter->x = data->plr->x + (x_dir  * adja);
            if (ft_is_wall(data, inter, 0, y_dir))
                break ;
        }
        inter->y += (y_dir * tl_ht);
    }
    return (sqrt((adja * adja) + (oppo * oppo)));
}

static double ft_ver_inter(t_data *data, t_point *inter, double angle)
{
    int         x_dir;
    int         y_dir;
    int         tl_wd;
    double      adja;
    double      oppo;

    tl_wd = data->tl_wd;
    inter->x = (data->plr->x / tl_wd) * tl_wd;
    x_dir = 1 - (2 * ((M_PI / 2) < angle && angle < \
        (M_PI + (M_PI / 2))));
    y_dir = 1 - (2 * (0 < angle && angle < M_PI));
    while ((0 < inter->x) && (inter->x < \
        (data->tl_wd * 20)))
    {
        if (((0 < x_dir) && (data->plr->x < inter->x)) || \
            ((x_dir < 0) && (inter->x < data->plr->x)))
        {
            adja = fabs(data->plr->x - inter->x);
            oppo = fabs(adja * tan(angle));
            inter->y = data->plr->y + (y_dir * oppo);
            if (ft_is_wall(data, inter, x_dir, 0))
                break ;
        }
        inter->x += (x_dir * tl_wd);
    }
    return (sqrt((adja * adja) + (oppo * oppo)));
}

double  ft_get_inter(t_data *data, t_point *inter, double angle)
{
    double      hor_dist;
    double      ver_dist;
    t_point     hor_inter;
    t_point     ver_inter;

    hor_dist = ft_hor_inter(data, \
        &hor_inter, angle);
    ver_dist = ft_ver_inter(data, \
        &ver_inter, angle);
    if (hor_dist <= ver_dist)
    {
        inter->x = hor_inter.x;
        inter->y = hor_inter.y;
        return (hor_dist);
    }
    else
    {
        inter->x = ver_inter.x;
        inter->y = ver_inter.y;
        return (ver_dist);
    }
    return (0);
}