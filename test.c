# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "MLX42/MLX42.h"
# include <stdarg.h>

typedef struct  s_point
{
    double         x;
    double         y;
}               t_point;


typedef struct  s_face
{
    char            dir;
    int             fix;
    int             rays;
    double          x_ref;
    double          y_ref;
    double          height_1;
    double          height_2;
    struct s_face   *next;
}                 t_face;

typedef struct  s_plr
{
    double          d;
    double          x;
    double          y;
}               t_plr;

typedef struct  s_data
{
    char            **map;
    int             wd_ht;
    int             wd_wh;
    int             tl_ht;
    int             tl_wd;
    t_plr           *plr;
    mlx_t           *mlx;
    t_point         *array;
    t_face          *face_lst;
    mlx_image_t     *rays_img;
    mlx_image_t     *wall_img;
    mlx_image_t     *ddd__img;
}               t_data;



void    ft_free_2d(char **arr)
{
    int     i;

    i = -1;
    if (arr)
    {
        while (arr && arr[++i])
            free(arr[i]);
        free(arr);
    }
}

static size_t   ft_strlen_sp(char const *s, char c)
{
    size_t      l;

    l = 0;
    while (s && s[l] && (s[l] != c))
        l++;
    return (l);
}

static int  ft_count_words(char const *s, char c)
{
    int         nbr;

    nbr = 0;
    while (s && *s)
    {
        if (*s && (*s != c))
        {
            while (*s && (*s != c))
                s++;
            nbr++;
        }
        else if (*s)
            s++;
    }
    return (nbr);
}

static char *ft_take_word(char const *s, char c)
{
    size_t      i;
    size_t      len;
    char        *word;

    i = -1;
    word = NULL;
    len = ft_strlen_sp(s, c);
    if (len)
    {
        word = malloc(sizeof(char) * (len + 1));
        if (!word)
            return (NULL);
        while (len--)
            word[++i] = *s++;
        word[++i] = '\0';
    }
    return (word);
}

char    **ft_split(char const *s, char c)
{
    int         i;
    int         wrds;
    char        **arr;

    i = -1;
    arr = NULL;
    wrds = ft_count_words(s, c);
    if (wrds)
    {
        arr = (char **)malloc(sizeof(char*) * (wrds + 1));
        if (!arr)
            return (NULL);
        while (*s)
        {
            while (*s && (*s == c))
                s++;
            if (*s)
                arr[++i] = ft_take_word(s, c);
            if (!arr[i])
                return (ft_free_2d(arr), NULL);
            s += ft_strlen_sp(arr[i], c);
        }
        arr[++i] = NULL;
    }
    return (arr);
}

static int  ft_render_line(t_data *data, t_face *tmp, double ht, double x)
{
    double      y;
    double      top;
    int         off_x;
    int         off_y;

    y = (data->wd_ht / 2) - (ht / 2); // pixel ofla
    if (tmp->fix == 1)
        off_x = (int)data->array[(int)x].x % 20;
    else
        off_x = (int)data->array[(int)x].y % 20;
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

void    ft_clear_image(mlx_image_t *img)
{
    int     i;
    int     j;

    j = -1;
    while (++j < img->height)
    {
        i = -1;
        while (++i < img->width)
            mlx_put_pixel(img, i, j, 0x00);
    }
}

static int  ft_check_next(t_data *data, double x, double y)
{
    if ((data->map[(int)((y + 3) / 20)][(int)(x / 20)] == '1') || \
        (data->map[(int)((y - 3) / 20)][(int)(x / 20)] == '1') || \
        (data->map[(int)(y / 20)][(int)((x + 3) / 20)] == '1') || \
        (data->map[(int)(y / 20)][(int)((x - 3) / 20)] == '1'))
        return (1);
    return (0);
}

static void ft_for_back_ward(t_data *data, int keycode)
{
    double      x;
    double      y;

    if (keycode == 87)
    {
        x = data->plr->x + (4 * cos(data->plr->d));
        y = data->plr->y + (4 * sin(data->plr->d) * -1);
    }
    else if (keycode == 83)
    {
        x = data->plr->x + (4 * cos(data->plr->d) * -1);
        y = data->plr->y + (4 * sin(data->plr->d));
    }
    if (!ft_check_next(data, x, y))
        (data->plr->x = x, data->plr->y = y);
}

static void ft_go_left_right(t_data *data, int keycode)
{
    double       x;
    double       y;
    double       angle;

    if (keycode == 65)
    {
        angle = real_angle(data->plr->d + \
            (M_PI / 2));
        x = data->plr->x + (double)(4 * cos(angle));
        y = data->plr->y + (double)(4 * sin(angle) * -1);
    }
    else if (keycode == 68)
    {
        angle = real_angle(data->plr->d + \
            (M_PI + (M_PI / 2)));
        x = data->plr->x + (double)(4 * cos(angle));
        y = data->plr->y + (double)(4 * sin(angle) * -1);
    }
    if (!ft_check_next(data, x, y))
        (data->plr->x = x, data->plr->y = y);
}

mlx_keyfunc ft_move_plr(mlx_key_data_t key, t_data *data)
{
    if (key.key == 65 || key.key == 68)
        ft_go_left_right(data, key.key);
    else if ((key.key == 83) || (key.key == 87))
        ft_for_back_ward(data, key.key);
    else if (key.key == 262)
        data->plr->d = real_angle(data->plr->d - \
            (double)(5 * (M_PI / 180)));
    else if (key.key == 263)
        data->plr->d = real_angle(data->plr->d + \
            (double)(5 * (M_PI / 180)));
    ft_clear_image(data->rays_img);
    ft_clear_image(data->ddd__img);
    ft_drop_rays(data);
    return (0);
}


static void get_dir(double angle, int *x_dir, int *y_dir)
{
    *x_dir = 1 - (2 * ((M_PI / 2) < angle && \
        angle < (M_PI + (M_PI / 2))));
    *y_dir = 1 - (2 * (0 < angle && angle < M_PI));
}

static int  is_wall(t_data *data, t_point *point, int x_d, int y_d)
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

static double hor_inter(t_data *data, t_point *inter, double angle)
{
    int         x_dir;
    int         y_dir;
    int         tl_ht;
    double      adja;
    double      oppo;

    tl_ht = data->tl_ht;
    get_dir(angle, &x_dir, &y_dir);
    inter->y = (int)(data->plr->y / tl_ht) * tl_ht;
    while ((0 < inter->y) && (inter->y < \
        (data->tl_ht * 20)))
    {
        if (((0 < y_dir) && (data->plr->y < inter->y)) || \
            ((y_dir < 0) && (inter->y < data->plr->y)))
        {
            oppo = fabs(data->plr->y - inter->y);
            adja = fabs(oppo / tan(angle));
            inter->x = data->plr->x + (x_dir  * adja);
            if (is_wall(data, inter, 0, y_dir))
                break ;
        }
        inter->y += (y_dir * tl_ht);
    }
    return (sqrt((adja * adja) + (oppo * oppo)));
}

static double ver_inter(t_data *data, t_point *inter, double angle)
{
    int         x_dir;
    int         y_dir;
    int         tl_wd;
    double      adja;
    double      oppo;

    tl_wd = data->tl_wd;
    get_dir(angle, &x_dir, &y_dir);
    inter->x = (int)(data->plr->x / tl_wd) * tl_wd;
    while ((0 < inter->x) && (inter->x < \
        (data->tl_wd * 20)))
    {
        if (((0 < x_dir) && (data->plr->x < inter->x)) || \
            ((x_dir < 0) && (inter->x < data->plr->x)))
        {
            adja = fabs(data->plr->x - inter->x);
            oppo = fabs(adja * tan(angle));
            inter->y = data->plr->y + (y_dir * oppo);
            if (is_wall(data, inter, x_dir, 0))
                break ;
        }
        inter->x += (x_dir * tl_wd);
    }
    return (sqrt((adja * adja) + (oppo * oppo)));
}

double  ft_get_inter(t_data *data, t_point *inter, double angle)
{
    double      tmp;
    double      dist;
    t_point     h_inter;
    t_point     v_inter;

    tmp = hor_inter(data, &h_inter, angle);
    dist = ver_inter(data, &v_inter, angle);
    if (tmp <= dist)
    {
        (inter->x = h_inter.x, inter->y = h_inter.y);
        dist = tmp;
    }
    else
        (inter->x = v_inter.x, inter->y = v_inter.y);
    return (dist);
}


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

    d_x = inter->x - data->plr->x;
    d_y = inter->y - data->plr->y;
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
    t_point     incr;
    t_point     start;

    i = -1;
    start.x = data->plr->x;
    start.y = data->plr->y;
    end = steps(data, inter, &incr);
    while (++i < end)
    {
        mlx_put_pixel(data->rays_img, start.x, \
            start.y, 0xffff000f);
        start.x += incr.x;
        start.y += incr.y;
    }
    return (0);
}

void    ft_drop_rays(t_data *data)
{
    int      x;
    double   rad;
    double   dst;
    double   incr;
    double   angle;
    t_point  inter;

    x = data->wd_wh;
    rad = (M_PI / 180);
    incr = ((60 * rad) / data->wd_wh);
    angle = real_angle(data->plr->d - \
        (30 * rad));
    while (x--)
    {
        angle = real_angle(angle);
        dst = ft_get_inter(data, &inter, angle);
        data->array[x].x = inter.x;
        data->array[x].y = inter.y;
        ft_draw_line(data, &inter);
        angle += incr;
    }
    ft_create_list(data);
    ft_render_wall(data);
}


void ft_free_lst(t_face *lst)
{
    t_face      *tmp;
    
    while (lst && lst->next)
    {
        tmp = lst;
        lst = lst->next;
        free (tmp);
    }
}

static t_face   *ft_create_node(double x_ref, double y_ref)
{
    t_face      *node;
    
    node = (t_face *)malloc(sizeof(t_face));
    node->height_1 = -1;
    node->x_ref = x_ref;
    node->y_ref = y_ref;
    node->rays = 0;
    node->fix = 0;
    node->next = NULL;
    return (node);
}

static double get_height(t_data *data, int i)
{
    double      oppo;
    double      adja;
    double      result;

    adja = fabs(data->plr->x - data->array[i].x);
    oppo = fabs(data->plr->y - data->array[i].y);
    result = ((100 * 100) / sqrt((oppo * oppo) + \
        (adja * adja)));
    return (result);
} 

static int create_sub_fun(t_data *data, t_face **tmp, int i)
{
    if (((*tmp)->fix == 1) && (data->array[i].x == (*tmp)->x_ref))
    {   
        if ((i == 759) || (data->array[i + 1].x != (*tmp)->x_ref))
            (*tmp)->height_2 = get_height(data, i);
    }
    else if (((*tmp)->fix == 2) && (data->array[i].y == (*tmp)->y_ref))
    {   
        if ((i == 759) || ( data->array[i + 1].y != (*tmp)->y_ref))
            (*tmp)->height_2 = get_height(data, i);
    }
    else
    {
        (*tmp)->next = ft_create_node(data->array[i].x, \
            data->array[i].y);
        if (!(*tmp)->next)
            return (-1);
        (*tmp) = (*tmp)->next;
    }
    return (0);
}

void    ft_create_list(t_data *data)
{
    int         i;
    t_face      *tmp;

    i = -1;
    tmp = ft_create_node(data->array[0].x, \
        data->array[0].y);
    data->face_lst = tmp;
    while (++i < 760)
    {
        if (tmp->fix == 0)
        {
            ((data->array[i].x != tmp->x_ref) && (tmp->fix = 2));
            ((data->array[i].y != tmp->y_ref) && (tmp->fix = 1));
            if (tmp->height_1 == -1)
                tmp->height_1 = get_height(data, i);
            if ((i == 759) || (data->array[i + 1].x != tmp->x_ref))
                tmp->height_2 = get_height(data, i);
        }
        else
            create_sub_fun(data, &tmp, i);
        tmp->rays++;
    }
}



void    ft_fill_img(mlx_image_t *img)
{
    int     i;
    int     j;

    j = 0;
    i = -1;
    while ((++i < img->width) && (j < img->height))
    {
        mlx_put_pixel(img, i, j, 0xff00000f);
        if ((i + 1) == img->width)
            (i = -1, j++);
    }
}

int ft_create_window(t_data  *data)
{
    if (!(data->mlx = mlx_init(data->wd_wh, data->wd_ht, \
        "cube", 0)))
        return (printf("data->mlx fails!!\n"));
    if (!(data->wall_img = mlx_new_image(data->mlx, \
        data->tl_wd, data->tl_ht)))
        return (printf("data->wall_img fails!!\n"));
    if (!(data->rays_img = mlx_new_image(data->mlx, \
        (data->tl_wd * 10), (data->tl_ht * 10))))
        return (printf("data->rays_img fails!!\n"));
    if (!(data->ddd__img = mlx_new_image(data->mlx, \
        data->wd_wh, data->wd_ht)))
        return (printf("data->ddd__img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->ddd__img, 0, 0))
        return (printf("data->ddd__img fails!!\n"));
    if (mlx_image_to_window(data->mlx, data->rays_img, 0, 0))
        return (printf("data.rays_img fails!!\n"));
    ft_fill_img(data->wall_img);
    return (0);
}

int main()
{
    t_plr   plr;
    char    *map = "1111111111 1000000001 1000010101 \
                    1110000001 1010110101 1010000001 \
                    1000000011 1010110001 1000000001 \
                    1111111111";
    t_data  data;

    plr.d = 0;
    plr.x = 30;
    plr.y = 30;
    data.tl_ht = 20;
    data.tl_wd = 20;
    data.wd_ht = 700;
    data.wd_wh = 760;
    data.plr = &plr;
    data.map = ft_split(map, ' ');
    if (!data.map)
        return (printf("ft_split fails!!\n"));
    data.array = (t_point *)malloc(sizeof(t_point) * data.wd_wh);
    if (!data.array)
        return (printf("arr allocation!!\n"));
    if (ft_create_window(&data))
        return (-1);
    mlx_key_hook(data.mlx, ft_move_plr, &data);
    mlx_load_png(NULL);
    // ft_mini_map(&data);
    mlx_loop(data.mlx);
    return (0);
}
