/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:36:16 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 22:02:18 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

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


typedef struct  s_door
{
    int             i;
    int             j;
    int             var;
    char            state;
}               t_door;

typedef struct  s_gun
{
    int             i;
    char            sht;
    int             nbr_sht;
    mlx_image_t     *arr[13];
}               t_gun;

typedef struct  s_data
{
    t_texture       north_text;
    t_texture       south_text;
    t_texture       west_text;
    t_texture       east_text;

	int32_t         c_color;
	int32_t         f_color;

	t_map			map;
    t_plr           plr;
    mlx_t           *mlx;

    int             wnd_ht;
    int             wnd_wd;
    int             grd_ht;
    int             grd_wd;
    int             doors_nbr;
    double          fact;
    
    t_gun           gun;
    t_door          *door_arr;

    t_point         *inter_arr;
    t_face          *face_lst;
    mlx_image_t     *map_img;
    mlx_image_t     *proj_img;
}               t_data;


# endif