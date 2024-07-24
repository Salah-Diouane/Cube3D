# ifndef CUBE_H
# define CUBE_H



# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>




# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "MLX42/MLX42.h"
# include <stdarg.h>

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
}                   t_face;

typedef struct  s_plr
{
    int         d;
    int      x;
    int      y;
}               t_plr;

typedef struct  s_data
{
    char        **map;
    int         wd_ht;
    int         wd_wh;
    int         tl_ht;
    int         tl_wd;
    t_plr       *plr;
    mlx_t       *mlx;
    t_point     *array;
    t_face      *face_lst;
    mlx_image_t *rays_img;
    mlx_image_t *wall_img;
    mlx_image_t *ddd__img;
}               t_data;

int         ft_real_angle(int angle);
void        ft_drop_rays(t_data *data);
void        ft_render_wall(t_data *data);
void        ft_create_list(t_data *data);
char        **ft_split(char const *s, char c);
mlx_keyfunc ft_move_plr(mlx_key_data_t key, t_data *data);
double      ft_get_inter(t_data *data, t_point *inter, double angle);

// parsing : 
char	**read_map();
char	**ft_split(char const	*s, char c);
// gnl : 
char	*ft_read_line(char *s);
char	*move_string(char *s);
char	*reader(int fd, char *reserve);
char	*get_next_line(int fd);
char	*ft_strdup(char *s1);
int	    find(char *s, char c);
int	    ft_strlen(char *s);
char	*ft_join(char *dest, char *s1, char *s2);
char	*ft_strjoin(char *start, char *buff);

# endif