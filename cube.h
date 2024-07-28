# ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "MLX42/MLX42.h"
// # include <mlx.h>
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
    mlx_texture_t   *wall;
	mlx_image_t		*img;
	int32_t			*texture_n;
	int32_t			*texture_s;
	int32_t			*texture_w;
	int32_t			*texture_e;
    char            **map;
    int             wnd_ht;
    int             wnd_wd;
    int             grd_ht;
    int             grd_wd;
    t_plr           plr;
    mlx_t           *mlx;
    t_point         *array;
    // t_texture       texture;
    t_face          *face_lst;
    mlx_image_t     *rays_img;
    mlx_image_t     *wall_img;
    mlx_image_t     *ddd__img;
}               t_data;


void        ft_update(t_data *data);
double      real_angle(double angle);
void		ft_set_img(t_data  *data);
void        ft_cast_rays(t_data *data);
void        ft_render_wall(t_data *data);
void        ft_create_list(t_data *data);
int			ft_mini_map(t_data *data);
char        **ft_split(char const *s, char c);
int32_t     *ft_get_img_n(mlx_image_t *img);
int32_t     *ft_get_img_s(mlx_image_t *img);
int32_t     *ft_get_img_w(mlx_image_t *img);
int32_t		*ft_get_img_e(mlx_image_t *img);
double      ft_get_inter(t_data *data, t_point *inter, double angle);

# endif
