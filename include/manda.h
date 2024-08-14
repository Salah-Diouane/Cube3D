/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:19:20 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/13 21:11:02 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MANDA_H
# define MANDA_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <MLX42.h>


typedef struct  s_point
{
    double         x;
    double         y;
}               t_point;

typedef struct  s_plr
{
    double          d;
    double          x;
    double          y;
}               t_plr;

typedef struct  s_face
{
    char            dir;
    char            fix;
    int             rays;
    double          height;
    struct s_face   *next;
}                t_face;

typedef struct  map
{
	int         wd;
	int         ht;
	char		**arr;
}               t_map;

typedef struct  s_texture
{
    char        *path;
    int32_t     *arr;
}               t_texture;

typedef struct  s_data
{

	int32_t         c_color;
	int32_t         f_color;

    int             wnd_ht;
    int             wnd_wd;
    int             grd_ht;
    int             grd_wd;
    
    t_plr           plr;
	t_map			map;
    mlx_t           *mlx;

    t_point         *inter_arr;
    t_face          *face_lst;
    mlx_image_t     *proj_img;
    
    t_texture       north_text;
    t_texture       west_text;
    t_texture       east_text;
    t_texture       south_text;
}               t_data;

/***************** ray casting animation functions *******************/

void        ft_move_plr(int key, t_data *arg);
void        free_lnkd_lst(t_face *lst);
void        free_map_text(t_data *data);
void        animate_plr(void *arg);
void        clean_up(t_data *data);
void        free_textures(t_data *data, int set);
int32_t     *get_texture_arr(t_data *data, char *path);
void        ft_cast_rays(t_data *data);
void        ft_clear_image(mlx_image_t *img);
char        **ft_split(char const *s, char c);
int         put_error(t_data *data, char *des, int set);
double      get_height(t_data *data, int i);
int         face_list(t_data *data);
mlx_image_t *load_image(t_data *data, char *path);
void        ft_render_wall(t_data *data);
double      real_angle(double angle);
int         ft_check_next(t_data *data, double angle);
void        ft_inter(t_data *data, t_point *inter, double angle);

# endif