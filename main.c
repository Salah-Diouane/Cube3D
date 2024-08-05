#include "cube.h"

static int ft_draw_cercle(mlx_image_t *img, double i, double j)
{
	double x;
	double y;
	double incr;
	double angle;
	int raduis;

	raduis = -1;
	incr = ((2 * M_PI) / 360);
	while (++raduis < 3)
	{
		angle = 0;
		while (angle < (2 * M_PI))
		{
			x = i + (raduis * cos(angle));
			y = j + (raduis * sin(angle));
			mlx_put_pixel(img, x, y, 0x0000ffff);
			angle += incr;
		}
	}
	return (0);
}

void ft_fill_img(t_data *data, mlx_image_t *img)
{
	int i;
	int j;

	j = 0;
	i = -1;
	while ((++i < img->width) && (j < img->height))
	{
		mlx_put_pixel(img, i, j, 0xffffff70);
		if ((i + 1) == img->width)
			(i = -1, j++);
	}
	ft_draw_cercle(data->wall_img, (data->wall_img->width / 2),
				   (data->wall_img->height / 2));
}

int ft_create_window(t_data *data)
{
	if (!(data->mlx = mlx_init(data->wnd_wd, data->wnd_ht, "cube", 0)))
		return (printf("data->mlx fails!!\n"));
	if (!(data->wall_img = mlx_new_image(data->mlx, 120, 120)))
		return (printf("data->wall_img fails!!\n"));
	if (!(data->rays_img = mlx_new_image(data->mlx, 120, 120)))
		return (printf("data->rays_img fails!!\n"));
	if (!(data->ignwan = mlx_load_png("textures/ignwan.png")))
		return (printf("data->ignwan fails!!\n"));
	if (!(data->ignwan_img = mlx_texture_to_image(data->mlx, data->ignwan)))
		return (printf("data->ignwan_img fails!!\n"));
	if (!(data->ddd__img = mlx_new_image(data->mlx,
										 data->wnd_wd, data->wnd_ht)))
		return (printf("data->ddd__img fails!!\n"));
	if (mlx_image_to_window(data->mlx, data->ignwan_img, 0, 0))
		return (printf("data->ddd__img fails!!\n"));
	if (mlx_image_to_window(data->mlx, data->ddd__img, 0, 0))
		return (printf("data->ddd__img fails!!\n"));
	if (mlx_image_to_window(data->mlx, data->wall_img, 2, 2))
		return (printf("data->wall__img fails!!\n"));
	if (mlx_image_to_window(data->mlx, data->rays_img, 0, 0))
		return (printf("data.rays_img fails!!\n"));
	ft_fill_img(data, data->wall_img);
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
	return (longest_length);
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
	char **new_map = (char **)g_malloc((rows + 1) * sizeof(char *), MALLOC);
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
		new_map[j] = (char *)g_malloc((longest_length + 1) * sizeof(char), MALLOC);
		if (!new_map[j])
		{
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
	// ft_free_2d(map);
	return new_map;
}

void f()
{
	system("leaks cube");
}

// crop : 512 ;resize : 128
int main(int arc, char **arv)
{
	t_data	data;
	t_map 	*map;
	t_text	*text;
	t_color	*col;
	int		longest_length;

	data.grd_ht = 64;
	data.grd_wd = 64;
	data.wnd_ht = 700;
	data.wnd_wd = 1060;
	map = (t_map *)g_malloc(sizeof(t_map), MALLOC);
	col = (t_color *)g_malloc(sizeof(t_color), MALLOC);
	text = (t_text *)g_malloc(sizeof(t_text), MALLOC);
	data.s_map = map;
	data.text = NULL;
	data.colors = NULL;
	t_col *head;
	atexit(f);
	if (ft_get_input(&data, arv) != 0)
		return (printf("----invalid map !!!\n"));
	if (ft_check_map(&data) != 0)
		return (printf("invalid map !!!\n"));
	longest_length = find_longest_line_length(data.s_map->map);
	data.s_map->map = create_new_map(data.s_map->map, longest_length, ft_get_rows(data.s_map->map));
	if (has_blank_lines_in_middle(data.s_map->map))
		return (printf("Error: Map contains blank lines in the middle\n"));
	// int i = 0;
	// while (data.s_map->map[i])
	// {
	// 	printf("|%s|\n", data.s_map->map[i++]);
	// }
	data.s_map->width = longest_length;
	data.s_map->width = ft_get_rows(data.s_map->map);

	// clear_all(&head);
}
