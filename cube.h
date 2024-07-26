# ifndef CUBE_H
# define CUBE_H

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
	int32_t			*texture;
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

double      real_angle(double angle);
void        ft_drop_rays(t_data *data);
void        ft_render_wall(t_data *data);
void        ft_create_list(t_data *data);
char        **ft_split(char const *s, char c);
mlx_keyfunc ft_move_plr(mlx_key_data_t key, t_data *data);
double      ft_get_inter(t_data *data, t_point *inter, double angle);

# endif