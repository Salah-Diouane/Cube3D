/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manda_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:43:12 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/13 15:33:28 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MANDA_PARSER_H
# define MANDA_PARSER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <limits.h>
# include "cube.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

typedef struct  s_color
{
	char		    *identif;
	int			    r;
	int			    g;
	int			    b;
	struct s_color   *next;
}               t_color;


/************************* parser functions *************************/

void    ft_free_2d(char **arr);
int	    ft_strcmp(char *s1, char *s2);
int	    ft_strncmp(char *s1, char *s2, int n);
char	*ft_strstr(char *str, char *to_find);
int     ft_parsing(t_data   *data, char **arv);
int     is_space(char c);
char	*ft_strdup(char *s1);
int	    ft_strlen(char *s);
int     just_space(char *str);
int     ft_get_rows(char **map);
int     ft_check_map(t_data *data);
char	**ft_read_map(char **arv);
int     ft_get_map(t_data *data, char **map);
int     ft_get_colors(t_data *data, char **map);
int     ft_get_texture(t_data *data, char **map);
int	    ft_get_last_index(char *line);
int	    ft_get_first_index(char *line);
int     ft_skip_last_spaces(char **map);
int     ft_check_around_elem(char **map);
int     ft_skip_first_spaces(char **map);
int     check_walls_and_elements(char **map);
int     ft_get_input(t_data *data, char **arv);
int     check_first_last_line(char **map);
int     ft_count_color_size(t_color *head);
char	*get_next_line(int fd);
char	*ft_strjoin(char *start, char *buff);
char	*ft_join(char *dest, char *s1, char *s2);
int	    ft_find(char *s, char c);
char    **ft_new_map(t_data *data, char **map);
int     set_player_position(t_data *data);
int     ft_atoi(char *str);
t_color *ft_n_clr(char *identif, int r, int g, int b);
void    ft_add_color(t_color **head, t_color *new_node);
int     ft_count_color_size(t_color *head);
void    free_color(t_color *color);
void    free_map(t_map *map);
char	*ft_strcpy(char *dest,  char *src);
char    *ft_strncpy(char *dest, const char *src, int n);
double  ft_get_direction(char **cp_map, int *i, int *j);

# endif