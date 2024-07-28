
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
	mlx_texture_t   *wall;
	mlx_image_t		*img;
	int32_t			*texture_n;
	int32_t			*texture_s;
	int32_t			*texture_w;
	int32_t			*texture_e;
	char            **map;
	char            **tab;
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

void ft_clear_image(mlx_image_t *img)
{
    int i;
    int j;

    j = -1;
    while (++j < img->height)
    {
        i = -1;
        while (++i < img->width)
            mlx_put_pixel(img, i, j, 0x00);
    }
}

static int ft_check_next(t_data *data, double x, double y)
{
    if ((data->map[(int)((y + 3) / 20)][(int)(x / 20)] == '1') ||
        (data->map[(int)((y - 3) / 20)][(int)(x / 20)] == '1') ||
        (data->map[(int)(y / 20)][(int)((x + 3) / 20)] == '1') ||
        (data->map[(int)(y / 20)][(int)((x - 3) / 20)] == '1'))
        return (1);
    return (0);
}

static void ft_for_back_ward(t_data *data, int keycode)
{
    double x;
    double y;

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
    double x;
    double y;
    double angle;

    if (keycode == 65)
    {
        angle = real_angle(data->plr->d + (M_PI / 2));
        x = data->plr->x + (double)(4 * cos(angle));
        y = data->plr->y + (double)(4 * sin(angle) * -1);
    }
    else if (keycode == 68)
    {
        angle = real_angle(data->plr->d + (M_PI + (M_PI / 2)));
        x = data->plr->x + (double)(4 * cos(angle));
        y = data->plr->y + (double)(4 * sin(angle) * -1);
    }
    if (!ft_check_next(data, x, y))
        (data->plr->x = x, data->plr->y = y);
}

void ft_update(t_data *data)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        ft_for_back_ward(data, 87);
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        ft_for_back_ward(data, 83);
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        ft_go_left_right(data, 65);
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        ft_go_left_right(data, 68);
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        data->plr->d = real_angle(data->plr->d - (double)(5 * (M_PI / 180)));
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        data->plr->d = real_angle(data->plr->d + (double)(5 * (M_PI / 180)));
    ft_clear_image(data->rays_img);
    ft_clear_image(data->ddd__img);
    ft_drop_rays(data);
}

void    ft_fill_img(mlx_image_t *img)
{
    int     i;
    int     j;

    j = 0;
    i = -1;
    while ((++i < img->width) && (j < img->height))
    {
        mlx_put_pixel(img, i, j, 0xff0000aa);
        if ((i + 1) == img->width)
            (i = -1, j++);
    }

    // for (j = 0; j < img->height / 2; j++)
    // {
    //     for (i = 0; i < img->width; i++)
    //     {
    //         mlx_put_pixel(img, i, j, 0x87CEEB);
    //     }
    // }
    // for (j = img->height / 2; j < img->height; j++)
    // {
    //     for (i = 0; i < img->width; i++)
    //     {
    //         mlx_put_pixel(img, i, j, 0x228B22);
    //     }
    // }
}

static int ft_mini_map(t_data *data)
{
    int     i;
    int     j;

    j = 0; 
    i = -1;
    while (data->map[j])
    {
        if (data->map[j][++i] == '1')
            mlx_image_to_window(data->mlx, \
                data->wall_img, (i * data->tl_wd), \
                (j * data->tl_ht));
        if (!data->map[j][(i + 1)])
            (i = -1, j++);
    }
    return (0);
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


static int ft_render_line(t_data *data, t_face *tmp, double ht, double x)
{
    double  y;
    double  top;
    int     off_x;
    int     off_y;
    int     width = data->img->width;
    int     height = data->img->height;

    y = (data->wd_ht / 2) - (ht / 2);
    if (tmp->fix == 1)
    {
        if (data->array[(int)x].x > data->plr->x)
        {
            data->face_lst->dir = 's';
            off_x = (int)((int)data->array[(int)x].y % data->tl_ht);
        }
        else
        {
            data->face_lst->dir = 'n';
            off_x = (int)((int)data->array[(int)x].y % data->tl_ht);
        }
    }
    else if (tmp->fix == 2)
    {
        if (data->array[(int)x].y > data->plr->y)
        {
            data->face_lst->dir = 'e';
            off_x = (int)((int)data->array[(int)x].x % data->tl_wd);
        }
        else
        {
            data->face_lst->dir = 'w';
            off_x = (int)((int)data->array[(int)x].x % data->tl_wd);
        }
    }
    top = y;
    while (y < ((data->wd_ht / 2) + (ht / 2)))
    {
        off_y = (y - top) * (20 / ht);
        if (0 <= y && y < data->img->height/*  && 0 <= x && x < data->img->width*/)
        {
            // mlx_put_pixel(data->img, x, y, data->texture_e[(data->tl_wd * off_y) + off_x]);
        }
        y = y + 4;
    }
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
    while (j < img->height / 2)
    {
        i = 0;
        while (i < img->width)
        {
            mlx_put_pixel(img, i, j, 0x87CEEB);
            i++;
        }
        j++;
    }
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



int main()
{
    t_plr   plr;
    char    *map = "1111111111 1000000001 1000010101 \
                    1100000001 1010110101 1010000001 \
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
    data.wall =  mlx_load_png("salah.png");
    data.img = mlx_texture_to_image(data.mlx, data.wall);
    ft_set_img(&data);
    int i = 0;
    while (i < ((data.img->width * data.img->height) * 4))
    {
        printf(" --> %x\n", data.texture_e[i]);
        i++;
    }
    mlx_loop_hook(data.mlx, ft_update, &data);
    ft_mini_map(&data);
    mlx_loop(data.mlx);
    return (0);
}
