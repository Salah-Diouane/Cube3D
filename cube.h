# ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "MLX42/MLX42.h"
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

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

typedef struct  s_text
{
	char		*identif;
	char		*chem;
	struct s_text   *next;
}               t_text;

typedef struct  s_color
{
	char		*identif;
	char		*value;
	struct s_color   *next;
}               t_color;

typedef struct  s_data
{
    mlx_texture_t   *wall_e;
    mlx_texture_t   *wall_w;
    mlx_texture_t   *wall_s;
    mlx_texture_t   *wall_n;

    mlx_texture_t   *ignwan;
	mlx_image_t		*ignwan_img;
    mlx_texture_t   *akal;
	mlx_image_t		*akal_img;

	mlx_image_t		*img_n;
	mlx_image_t		*img_s;
	mlx_image_t		*img_w;
	mlx_image_t		*img_e;

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
    t_face          *face_lst;
    mlx_image_t     *rays_img;
    mlx_image_t     *wall_img;
    mlx_image_t     *ddd__img;

	t_text			*text;
	t_color			*colors;
}               t_data;

// Parsing :
int		ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*get_next_line(int fd);
char	*ft_read_line(char *s);
int		ft_find(char *s, char c);
char	*ft_move_string(char *s);
char	**ft_read_map(char **arv);
char	**ft_read_map(char **arv);
int		ft_is_identifier(char *line);
int		ft_count_map_line(char **map);
char	*reader(int fd, char *reserve);
int		ft_count_text_size(t_text *head);
int		ft_count_color_size(t_color *head);
int		ft_get_map(t_data *data, char **map);
int		ft_get_map(t_data *data, char **map);
char	*ft_strjoin(char *start, char *buff);
int 	ft_get_input(t_data *data, char **arv);
int		ft_get_colors(t_data *data, char **map);
int		ft_get_texture(t_data *data, char **map);
int		ft_get_texture(t_data *data, char **map);
char	*ft_join(char *dest, char *s1, char *s2);
t_color *ft_new_color(char *identif, char *value);
t_text	*ft_new_texture(char *identif, char *chem);
t_text	*ft_new_texture(char *identif, char *chem);
void	ft_add_texture(t_text **head, t_text *new_node);
void	ft_add_texture(t_text **head, t_text *new_node);
void	ft_add_color(t_color **head, t_color *new_node);

// Execution :
double      real_angle(double angle);
int			ft_mini_map(t_data *data);
void		ft_set_img(t_data  *data);
void        ft_cast_rays(t_data *data);
void        ft_render_wall(t_data *data);
void        ft_create_list(t_data *data);
int32_t     *ft_get_img_n(mlx_image_t *img);
int32_t     *ft_get_img_s(mlx_image_t *img);
int32_t     *ft_get_img_w(mlx_image_t *img);
int32_t		*ft_get_img_e(mlx_image_t *img);
char        **ft_split(char const *s, char c);
mlx_keyfunc ft_move_plr(mlx_key_data_t key, t_data *data);
double      ft_get_inter(t_data *data, t_point *inter, double angle);

# endif
