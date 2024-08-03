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

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# define END '\0'
# define NLN '\n'

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
	// N = 90 s = 270  w = 180  e 360
	// x =	i  * 64, y = j * 64
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
int		just_space(char *str);
char	*get_next_line(int fd);
char	*ft_read_line(char *s);
int		ft_get_cols(char **map);
int		ft_get_rows(char **map);
int		ft_find(char *s, char c);
char	*ft_move_string(char *s);
int		is_space(unsigned char c);
char	**ft_read_map(char **arv);
char	**ft_read_map(char **arv);
int		ft_check_map(t_data *data);
int		ft_check_map(t_data *data);
char	*trim_whitespace(char *str);
int		is_all_ones(const char *str);
int		ft_is_identifier(char *line);
int		ft_check_content(char *line);
int		find_longest_line(char **map);
int		ft_count_map_line(char **map);
int		ft_check_elements(char *line);
char	*reader(int fd, char *reserve);
int		ft_first_check_map(t_data *data);
int		ft_count_text_size(t_text *head);
int		ft_second_check_map(t_data *data);
int		ft_count_color_size(t_color *head);
int		ft_check_position_of_zero(char **cp_map, int *i, int *j);
int		ft_get_map(t_data *data, char **map);
char	*ft_strjoin(char *start, char *buff);
int 	ft_get_input(t_data *data, char **arv);
int		check_walls_and_elements(t_data *data, char **cp_map);
int		ft_get_colors(t_data *data, char **map);
int		ft_get_texture(t_data *data, char **map);
int		ft_get_texture(t_data *data, char **map);
char	*ft_join(char *dest, char *s1, char *s2);
t_color *ft_new_color(char *identif, int r, int g, int b);
t_text	*ft_new_texture(char *identif, char *chem);
t_text	*ft_new_texture(char *identif, char *chem);
int		check_first_last_line(char **cp_map, int j);
void	ft_add_texture(t_text **head, t_text *new_node);
void	ft_add_texture(t_text **head, t_text *new_node);
void	ft_add_color(t_color **head, t_color *new_node);
int		is_closed_by_walls(char **map, int rows, int cols);
int		populate_cp_map(t_data *data, char **cp_map, int *i, int *j);
int		initialize_cp_map(t_data *data, char ***cp_map, int *rows);
int		populate_cp_map_without_trimming(t_data *data, char **cp_map, int *i, int *j);


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
