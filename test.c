

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

    t_text          *text;
    t_color         *colors;
} t_data;



t_color *ft_new_color(char *identif, int r, int g, int b)
{
    t_color *new_node;

    new_node = (t_color *)malloc(sizeof(t_color));
    if (!new_node)
        return (NULL);
    new_node->identif = ft_strdup(identif);
    new_node->r = r;
    new_node->g = g;
    new_node->b = b;
    new_node->next = NULL;
    return (new_node);
}

void ft_add_color(t_color **head, t_color *new_node)
{
    t_color *current;

    if (!head || !new_node)
        return;
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

int ft_count_color_size(t_color *head)
{
    int count;
    t_color *current;

    count = 0;
    current = head;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

int process_color_line(t_data *data, char *line, int *c_count, int *f_count)
{
    char **tmp;
    char **col;
    t_color *color = NULL;

    if (!strncmp(line, "C", 1))
        (*c_count)++;
    else if (!strncmp(line, "F", 1))
        (*f_count)++;
    tmp = ft_split(line, ' ');
    if (tmp[2] != NULL || (!tmp[0] || !tmp[1]))
        return printf("COLORS : error more than one argument in texture\n");
    col = ft_split(tmp[1], ',');
    if (col[0] && col[1] && col[2])
    {
        if ((atoi(col[0]) < 0 || atoi(col[0]) > 255) || (atoi(col[1]) < 0
			|| atoi(col[1]) > 255) || (atoi(col[2]) < 0 || atoi(col[2]) > 255))
            return printf("invalid rgb \n");
        color = ft_new_color(tmp[0], atoi(col[0]), atoi(col[1]), atoi(col[2]));
    }
    if (color)
        ft_add_color(&data->colors, color);
    else
        return printf("Memory allocation failed\n");
    ft_free_2d(tmp);
    ft_free_2d(col);
    return (0);
}

int ft_get_colors(t_data *data, char **map)
{
    int i;
    int c_count;
    int f_count;

    c_count = 0;
    f_count = 0;
    i = 0;
    while (map[i])
    {
        map[i][strlen(map[i])] = '\0';
        if (!strncmp(map[i], "C", 1) || !strncmp(map[i], "F", 1))
        {
            if (process_color_line(data, map[i], &c_count, &f_count))
                return (1);
        }
        i++;
    }
    if (c_count != 1 || f_count != 1)
        return (printf("Error: There must be exactly one 'C' and one 'F'\n"));
    return (0);
}





t_text	*ft_new_texture(char *identif, char *chem)
{
	t_text  *new_node;

	new_node = (t_text *)malloc(sizeof(t_text));
	if (!new_node)
		return (NULL);
	new_node->identif = ft_strdup(identif);
	new_node->chem = ft_strdup(chem);
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_texture(t_text **head, t_text *new_node)
{
	t_text  *current;

	if (!head || !new_node)
		return;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current && current->next)
		current = current->next;
    if (current)
       current->next = new_node;
}

int ft_count_text_size(t_text *head)
{
    int     count;
    t_text  *current;

    count = 0;
    current = head;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

int process_texture_line(t_data *data, char *line, int *no_count, int *so_count, int *we_count, int *ea_count)
{
    char **tmp;
    t_text *txt;
    
    // data->text = (t_text *)malloc(sizeof(t_text));
    if (!strncmp(line, "NO", 2))
        (*no_count)++;
    else if (!strncmp(line, "SO", 2))
        (*so_count)++;
    else if (!strncmp(line, "WE", 2))
        (*we_count)++;
    else if (!strncmp(line, "EA", 2))
        (*ea_count)++;
    tmp = ft_split(line, ' ');
    if (tmp[2] != NULL)
        return (printf("TEXTURES : error more than one argument in texture\n"));
    txt = ft_new_texture(tmp[0], tmp[1]);
    if (!txt)
        return (printf("ft_new_texture fails!!\n"));
    ft_add_texture(&data->text, txt);
    ft_free_2d(tmp);
    return (0);
}

int ft_get_texture(t_data *data, char **map)
{
    int i = 0;
    int no_count = 0;
    int so_count = 0;
    int we_count = 0;
    int ea_count = 0;

    while (map[i])
    {
        map[i][ft_strlen(map[i])] = '\0';
        if (!strncmp(map[i], "NO", 2) || !strncmp(map[i], "SO", 2) ||
            !strncmp(map[i], "WE", 2) || !strncmp(map[i], "EA", 2))
        {
            if (process_texture_line(data, map[i], &no_count, &so_count, &we_count, &ea_count))
                return 1;
        }
        i++;
    }
    if (no_count != 1 || so_count != 1 || we_count != 1 || ea_count != 1)
        return printf("Error: There must be exactly one 'NO', 'SO', 'WE', and 'EA'\n");
    return 0;
}





int	ft_check_len_color(t_color	*color)
{
	t_color	*tmp;

	tmp = color;
	while (tmp)
	{
		if (ft_strlen(tmp->identif) != 1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_len_txt(t_text	*color)
{
	t_text	*tmp;

	tmp = color;
	while (tmp)
	{
		if (ft_strlen(tmp->identif) != 2)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int is_texture_or_color(char *line)
{
    return (!strncmp(line, "NO", 2) || !strncmp(line, "SO", 2) ||
            !strncmp(line, "WE", 2) || !strncmp(line, "EA", 2) ||
            !strncmp(line, "C", 1) || !strncmp(line, "F", 1));
}

int validate_elements_position(char **map)
{
    int i = 0;
    int found_non_texture_or_color = 0;

    while (map[i])
    {
        if (just_space(map[i]) == 0)
        {
            i++;
            continue;
        }

        if (is_texture_or_color(map[i]))
        {
            if (found_non_texture_or_color)
                return (-1);
        }
        else
        {
            found_non_texture_or_color = 1;
        }

        i++;
    }
    return 0;
}

int ft_get_input(t_data *data, char **arv)
{
	char    **map;

	map = ft_read_map(arv);
	if (!map)
		return (ft_free_2d(map), printf("invalid map !!!\n"));
	if (validate_elements_position(map) != 0)
		return (ft_free_2d(map), printf("ft_check_order fails!!\n"));
	if (ft_get_map(data, map) != 0)
		return (ft_free_2d(map), printf("ft_get_map fails!!\n"));
	if (ft_get_colors(data, map) != 0 || ft_count_color_size(data->colors) != 2)
		return (ft_free_2d(map), printf("ft_get_colors fails!!\n"));
	if (ft_get_texture(data, map) != 0 || ft_count_text_size(data->text) != 4
			|| ft_check_len_txt(data->text) == -1)
		return (ft_free_2d(map), printf("ft_get_texture fails!!\n"));
	ft_free_2d(map);
	return (0);
}

















































int find_longest_line_length(char **map)
{
	int longest_length = 0;
	int length;
	int i = 0;

	while (map[i] != NULL)
	{
		length = strlen(map[i]);
		if (length > longest_length)
		{
			longest_length = length;
		}
		i++;
	}
	return longest_length;
}


int find_longest_line(char **map)
{
	int longest_length;
	int longest_index;
	int length;
	int rows;
	int i;

	i = 0;
	longest_length = 0;
	longest_index = -1;
	rows = ft_get_rows(map);
	while (i < rows)
	{
		length = ft_strlen(map[i]);
		if (length > longest_length)
		{
			longest_length = length;
			longest_index = i;
		}
		i++;
	}
	return (longest_index);
}

int has_blank_lines_in_middle(char **map)
{
    int found_non_empty = 0;
    int i = 0;

    while (map[i])
    {
        if (just_space(map[i]) == 0)
        {
            if (found_non_empty)
                return (1);
        }
        else
            found_non_empty = 1;
        i++;
    }
    return (0);
}

char **create_new_map(char **map, int longest_length, int rows)
{
	char **new_map = (char **)malloc((rows + 1) * sizeof(char *));
	if (!new_map)
		return NULL;

	int i = 0, j = 0;
	while (map[i])
	{
		if (just_space(map[i]) == 0)
			i++;
		else
			break;
	}
	while (map[i] != NULL)
	{
		new_map[j] = (char *)malloc((longest_length + 1) * sizeof(char));
		if (!new_map[j])
		{
			for (int k = 0; k < j; k++)
			{
				free(new_map[k]);
			}
			free(new_map);
			return NULL;
		}
		strcpy(new_map[j], map[i]);
		int len = strlen(new_map[j]);
		for (int k = len; k < longest_length; k++)
		{
			new_map[j][k] = ' ';
		}
		new_map[j][longest_length] = '\0';
		j++;
		i++;
	}
	new_map[j] = NULL;
	ft_free_2d(map);
	return new_map;
}

void f()
{
	system("leaks cube");
}

void free_text(t_text *text)
{
    t_text *temp;

    while (text != NULL)
    {
        temp = text;
        text = text->next;
        free(temp->identif);
        free(temp->chem);
        free(temp);
    }
}

void free_color(t_color *color)
{
    t_color *temp;

    while (color != NULL)
    {
        temp = color;
        color = color->next;
		if (temp->identif)
			free(temp->identif);
		else
			break ;
        free(temp);
    }
}

// crop : 512 ;resize : 128
int main(int arc, char **arv)
{
	t_data	data;
	int		longest_length;
	// char *map = "1111111111 1000000001 1000010101 \
    //                 1100000001 1010110101 1010000001 \
    //                 1000000011 1010110001 1000000001 \
    //                 1111111111";

	data.plr.d = 0;
	data.plr.x = 140;
	data.plr.y = 140;
	data.grd_ht = 128;
	data.grd_wd = 128;
	data.wnd_ht = 700;
	data.wnd_wd = 1060;

	// atexit(f);
	// data.map = ft_split(map, ' ');
	data.colors = (t_color *)malloc(sizeof(t_color));
	data.text = (t_text *)malloc(sizeof(t_text));
	if (ft_get_input(&data, arv) != 0)
	{
		// if (data.map[0])
		// 	ft_free_2d(data.map);
		return (printf("----invalid map !!!\n"));
	}
	if (ft_check_map(&data) != 0)
		return (ft_free_2d(data.map), free_color(data.colors), free_text(data.text),  printf("invalid map !!!\n"));
	longest_length = find_longest_line_length(data.map);
	data.map = create_new_map(data.map, longest_length, ft_get_rows(data.map));
	if (has_blank_lines_in_middle(data.map))
		return (ft_free_2d(data.map), free_color(data.colors), free_text(data.text),  printf("Error: Map contains blank lines in the middle\n"));
	int i = 0;
	while (data.map[i])
	{
		printf("|%s|\n", data.map[i++]);
	}
	ft_free_2d(data.map);
	free_color(data.colors);
	free_text(data.text);
}
















