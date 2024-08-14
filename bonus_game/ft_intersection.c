# include "../include/bonus.h"

static void get_dir(double angle, t_point *dir)
{
    dir->x = 1 - (2 * ((M_PI / 2) < angle && \
        angle < (M_PI + (M_PI / 2))));
    dir->y = 1 - (2 * (0 < angle && angle < M_PI));
}

static int  is_wall(t_data *dt, t_point *p, int x_d, int y_d)
{
    int         i;
    int         j;
    t_door      *door;

    i = (p->x / dt->grd_wd) - (1 * (x_d < 0));
    j = (p->y / dt->grd_ht) - (1 * (y_d < 0));
    if ((p->x < 0) || (p->y < 0) || ((dt->grd_wd * dt->map.wd) < \
        p->x) || ((dt->grd_ht * dt->map.ht) < p->y))
        return (1);
    else if (dt->map.arr[j][i] == '1')
        return (1);
    else if (dt->map.arr[j][i] == 'd')
    {
        door = get_door(dt, i, j);
        if (door && (x_d) && (((p->y < (j * dt->grd_ht + \
            door->var)) || (((j * dt->grd_ht + 64) - \
                door->var) < p->y))))
            return (1);
        else if (door && (y_d) && ((p->x < (i * dt->grd_wd + \
            door->var)) || (((i * dt->grd_wd + 64) - \
                door->var) < p->x)))
            return (1);
    }
    return (0);
}

static double hor_inter(t_data *data, t_point *inter, double angle)
{
    t_point     dir;
    t_point     agle;
    int         grd_ht;

    get_dir(angle, &dir);
    grd_ht = data->grd_ht;
    inter->y = (int)(data->plr.y / grd_ht) * grd_ht;
    while ((0 < inter->y) && (inter->y < (grd_ht * data->map.ht)))
    {
        if (((0 < dir.y) && (data->plr.y < inter->y)) || \
            ((dir.y < 0) && (inter->y < data->plr.y)))
        {
            agle.y = fabs(data->plr.y - inter->y);
            agle.x = fabs(agle.y / tan(angle));
            inter->x = data->plr.x + (dir.x  * agle.x);
            if (is_wall(data, inter, 0, dir.y))
                break ;
        }
        inter->y += (dir.y * grd_ht);
    }
    return (sqrt((agle.x * agle.x) + (agle.y * agle.y)));
}

static double ver_inter(t_data *data, t_point *inter, double angle)
{
    t_point     dir;
    t_point     agle;
    int         grd_wd;

    get_dir(angle, &dir);
    grd_wd = data->grd_wd;
    inter->x = (int)(data->plr.x / grd_wd) * grd_wd;
    while ((0 < inter->x) && (inter->x < (grd_wd * data->map.wd)))
    {
        if (((0 < dir.x) && (data->plr.x < inter->x)) || \
            ((dir.x < 0) && (inter->x < data->plr.x)))
        {
            agle.x = fabs(data->plr.x - inter->x);
            agle.y = fabs(agle.x * tan(angle));
            inter->y = data->plr.y + (dir.y * agle.y);
            if (is_wall(data, inter, dir.x, 0))
                break ;
        }
        inter->x += (dir.x * grd_wd);
    }
    return (sqrt((agle.x * agle.x) + (agle.y * agle.y)));
}

void  ft_inter(t_data *dt, t_point *inter, double angle)
{
    t_point     hypo;
    t_point     h_inter;
    t_point     v_inter;

    if (dt && inter && dt->map.arr)
    {
        hypo.x = hor_inter(dt, \
            &h_inter, angle);
        hypo.y = ver_inter(dt, \
            &v_inter, angle);
        if (hypo.x <= hypo.y)
        {
            inter->x = h_inter.x;
            inter->y = h_inter.y; 
        }
        else
        {
            inter->x = v_inter.x;
            inter->y = v_inter.y;
        }
    }
}
