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

void f()
{
	system("leaks cube");
}
int ft_get_rows(char **map)
{
	int rows;
	
	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
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
	data.s_map = map;
	data.text = NULL;
	data.colors = NULL;
	t_col *head;
	// atexit(f);
	if (ft_get_input(&data, arv) != 0)
		return (-1);
	if (ft_check_map(&data) != 0)
		return (printf("invalid map !!!\n"));
	data.s_map->map = ft_new_map(data.s_map->map);
	if (!data.s_map->map)
		return (-1);
	int i = 0;
	printf("\nAFTER : \n");
	while (data.s_map->map[i])
	{
		printf("|%s|\n", data.s_map->map[i++]);
	}

	data.s_map->width = longest_length;
	data.s_map->width = ft_get_rows(data.s_map->map);

	// clear_all(&head);
}
