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
#include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# define END '\0'
# define NLN '\n'

typedef struct s_col
{
	void			*ptr;
	struct s_col	*next;
}					t_col;

typedef enum e_call
{
	FREE,
	MALLOC
}	t_call;

typedef struct  s_bool
{
	bool has_one;
	bool has_zero;
	bool has_nsew;

}				t_bool;


typedef struct  s_point
{
	double         x;
	double         y;
}				t_point;


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
	int			r;
	int			g;
	int			b;
	struct s_color   *next;
}               t_color;

typedef struct  s_map
{
	char		**map;
	int         width;
	int         height;
}               t_map;

typedef struct s_data
{
	mlx_texture_t   *wall_e;
	mlx_texture_t   *wall_w;
	mlx_texture_t   *wall_s;
	mlx_texture_t   *wall_n;

	mlx_texture_t   *ignwan;
	mlx_image_t     *ignwan_img;
	mlx_texture_t   *akal;
	mlx_image_t     *akal_img;

	mlx_image_t     *img_n;
	mlx_image_t     *img_s;
	mlx_image_t     *img_w;
	mlx_image_t     *img_e;

	int32_t         *texture_n;
	int32_t         *texture_s;
	int32_t         *texture_w;
	int32_t         *texture_e;

	t_map			*s_map;
	t_bool			v_bool;

	int             doors_nbr;;

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

	t_text          *text;
	t_color         *colors;
} t_data;

// g_collecter : 
void	clear_all(t_col **head);
void	*g_malloc(size_t size, t_call call);

// Parsing :
int is_space(char c);
char	*ft_strdup(char *s1);
int	ft_strlen(char *s);
int just_space(char *str);
int ft_get_rows(char **map);
int ft_check_map(t_data *data);
char	**ft_read_map(char **arv);
int ft_get_map(t_data *data, char **map);
int ft_get_colors(t_data *data, char **map);
int ft_get_texture(t_data *data, char **map);
int	ft_get_last_index(char *line);
int	ft_get_first_index(char *line);
int ft_skip_last_spaces(char **map);
int ft_check_around_elem(char **map);
int ft_skip_first_spaces(char **map);
int check_walls_and_elements(char **map);
int ft_get_input(t_data *data, char **arv);
int check_first_last_line(char **map);
int ft_count_color_size(t_color *head);
int ft_count_text_size(t_text *head);
char	*get_next_line(int fd);
char	*ft_strjoin(char *start, char *buff);
char	*ft_join(char *dest, char *s1, char *s2);
int	ft_find(char *s, char c);
char **ft_new_map(char **map);


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
