
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "MLX42/MLX42.h"
# include <stdarg.h>
# include <fcntl.h>


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
    mlx_t           *mlx;
    mlx_image_t     *rays_img;
    mlx_image_t     *wall_img;
    mlx_image_t     *ddd__img;

	t_text			*text;
	t_color			*colors;
}               t_data;

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
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
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

int ft_get_texture(t_data *data, char **map)
{
	t_text	*txt;
	char	**tmp;
	int		i;

	(1) && (i = 0, txt = NULL, tmp = NULL);
	while (map[i])
	{
		map[i][ft_strlen(map[i])] = '\0';
		if (!strncmp(map[i], "NO", 2) || !strncmp(map[i], "SO", 2) ||
			!strncmp(map[i], "WE", 2) || !strncmp(map[i], "EA", 2))
		{
			tmp = ft_split(map[i], ' ');
			if (tmp[2] != NULL)
				return (printf("TEXTURES : error more than onr args in texture\n"));
			txt = ft_new_texture(tmp[0], tmp[1]);
			if (!txt)
				return (printf("ft_new_texture fails!!\n"));
			ft_add_texture(&data->text, txt);
			free(tmp[0]);
			free(tmp[1]);
			free(tmp);
		}
		i++;
	}
	return (0);
}








t_color *ft_new_color(char *identif, char *value)
{
    t_color *new_node;

    new_node = (t_color *)malloc(sizeof(t_color));
    if (!new_node)
        return (NULL);
    new_node->identif = ft_strdup(identif);
    new_node->value = ft_strdup(value);
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
    int     count;
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

int ft_get_colors(t_data *data, char **map)
{
    t_color *color;
    char **tmp;
    int i;

    (1) && (i = 0, color = NULL, tmp = NULL);
    while (map[i])
    {
		map[i][ft_strlen(map[i])] = '\0';
        if (!strncmp(map[i], "C", 1) || !strncmp(map[i], "F", 1))
        {
            tmp = ft_split(map[i], ' ');
			if (tmp[2] != NULL)
				return (printf("COLORS : error more than onr args in texture\n"));
			color = ft_new_color(tmp[0], tmp[1]);
			if (color)
				ft_add_color(&data->colors, color);
			else
				return (printf("Memory allocation failed\n"));
            free(tmp[0]);
            free(tmp[1]);
            free(tmp);
        }
        // else
        //     return (-1);
        i++;
    }
    return (0);
}



char	**ft_read_map(char **arv)
{
	char	*line;
	char	*tmp;
	char	**all;
	int     fd;

	fd = open(arv[1], O_RDONLY, 0777);
	line = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		line = ft_strjoin(line, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	all = ft_split(line, '\n');
	free(line);
	return (all);
}


int ft_check(char *str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (-1);
	}
	return (i);
}

int	ft_get_map(t_data *data, char **map)
{
	int		i;
	int		j;
	int		map_start;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (ft_check(map[i]) != -1)
		{
			data->map[j] = ft_strdup(map[i]);
			j++;
		}
			i++;
	}
	// data->map = &map[map_start];
	if (!data->map)
		return (printf("data->map fails!!\n"));
	return (0);
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

int ft_get_input(t_data *data, char **arv)
{
	char    **map;

	map = ft_read_map(arv);
	if (!map)
		return (printf("ft_read_map fails!!\n"));
	if (ft_get_map(data, map) != 0)
		return (printf("ft_get_map fails!!\n"));
	if (ft_get_texture(data, map) != 0 || ft_count_text_size(data->text) != 4
			|| ft_check_len_txt(data->text) == -1)
		return (printf("ft_get_texture fails!!\n"));
	if (ft_get_colors(data, map) != 0 || ft_count_color_size(data->colors) != 2
			|| ft_check_len_color(data->colors) == -1)
		return (printf("ft_get_colors fails!!\n"));
	return (0);
}
