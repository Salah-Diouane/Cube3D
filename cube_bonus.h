# ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "../MLX42/MLX42.h"
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>


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

typedef struct  s_text
{
	char		*identif;
	char		*chem;
    int32_t     *pix_arr;
	struct s_text   *next;
}               t_text;

typedef struct  s_point
{
    double         x;
    double         y;
}               t_point;

typedef struct  s_door
{
    int             i;
    int             j;
    int             var;
    char            state;
}               t_door;

typedef struct  s_plr
{
    double          d;
    double          h;
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

typedef struct  s_color
{
	char		*identif;
	int			r;
	int			g;
	int			b;
	struct s_color   *next;
}               t_color;

typedef struct  map
{
	char		**map;
	int         width;
	int         height;
}               t_map;

typedef struct  s_gun
{
    int             i;
    char            sht;
    int             nbr_sht;
    mlx_image_t     *arr[13];
}               t_gun;

typedef struct s_texture_count
{
    int no_count;
    int so_count;
    int we_count;
    int ea_count;
} t_text_count;

typedef struct  s_texture
{
    char        *path;
    int32_t     *arr;
}               t_texture;

typedef struct  s_data
{
    t_texture       north_text;
    t_texture       south_text;
    t_texture       west_text;
    t_texture       east_text;

	int32_t         c_color;
	int32_t         f_color;

	t_map			*map;
	t_bool			v_bool;
    int             wnd_ht;
    int             wnd_wd;
    int             grd_ht;
    int             grd_wd;
    int             doors_nbr;
    t_plr           plr;
    t_gun           gun;
    double          fact;
    mlx_t           *mlx;

    t_point         *inter_arr;
    t_door          *door_arr;
    t_face          *face_lst;
    mlx_image_t     *map_img;
    mlx_image_t     *proj_img;
    t_text			*text;
	t_color			*colors;
    t_text_count    *txt_count;
}               t_data;



// Parsing :
void    ft_free_2d(char **arr);

int ft_parsing(t_data   *data, char **arv);
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
char **ft_new_map(t_data *data, char **map);
int set_player_position(t_data *data);
int ft_atoi(char *str);
t_color *ft_n_clr(char *identif, int r, int g, int b);
void ft_add_color(t_color **head, t_color *new_node);
int ft_count_color_size(t_color *head);
void free_texture(t_text *head);
void free_color(t_color *color);
void free_map(t_map *map);
char	*ft_strcpy(char *dest,  char *src);
char *ft_strncpy(char *dest, const char *src, int n);
double ft_get_direction(char **cp_map, int *i, int *j);
int32_t *get_texture_arr(t_data *data, char *path);


void        ft_move_plr(int key, t_data *arg);
int         ft_free_lst(t_face *lst);
int         ft_door_ctl(t_data *data);
void        animation(t_data *data);
void        animate_plr(t_data *data);
int         init_gun_arr(t_data *data);
int         ft_mini_map(t_data *data);
int         delete_imgs(t_data *data, int size);
void        ft_cast_rays(t_data *data);
void        ft_clear_image(mlx_image_t *img);
char        **ft_split(char const *s, char c);
double      get_height(t_data *data, int i);
void        shut(t_data *data);
t_face      *face_list(t_data *data);
void        ft_render_wall(t_data *data);
void        fill_door_array(t_data *data);
t_door      *get_door(t_data *data, int i, int j);
double      real_angle(double angle);
int         ft_check_next(t_data *data, double x, double y);
void        ft_inter(t_data *data, t_point *inter, double angle);
# endif