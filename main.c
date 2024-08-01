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

char **create_new_map(char **map, int longest_length, int rows)
{
	char **new_map = (char **)malloc((rows + 1) * sizeof(char *));
	if (!new_map)
		return NULL;

	int i = 0, j = 0;
	while (map[i])
	{
		if (just_space(map[i]) == 1)
		{
			i++;
		}
		else
		{
			break;
		}
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
	return new_map;
}

// crop : 512 ;resize : 128
int main(int arc, char **arv)
{
	t_data data;
	char *map = "1111111111 1000000001 1000010101 \
                    1100000001 1010110101 1010000001 \
                    1000000011 1010110001 1000000001 \
                    1111111111";

	data.plr.d = 0;
	data.plr.x = 140;
	data.plr.y = 140;
	data.grd_ht = 128;
	data.grd_wd = 128;
	data.wnd_ht = 700;
	data.wnd_wd = 1060;

	// data.map = ft_split(map, ' ');
	if (ft_get_input(&data, arv) != 0)
		return (printf("invalid map !!!\n"));
	if (ft_check_map(&data) != 0)
		return (printf("invalid map !!!\n"));

	int i = 0;
	printf("BEFORE : \n");
	i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	int longest_length = find_longest_line_length(data.map);
	data.map = create_new_map(data.map, longest_length, ft_get_rows(data.map));
	printf("AFTER : \n");
	i = 0;
	while (data.map[i])
	{
		printf("|%s|\n", data.map[i]);
		i++;
	}

	// printf("----> Textures : \n");
	// while (data.text)
	// {
	//     printf("identif : %s\tchemin : %s\n", data.text->identif, data.text->chem);
	//     data.text = data.text->next;
	// }

	// printf("----> Colors : \n");
	// while (data.colors)
	// {
	//     printf("color : %s\tvalue : %s\n", data.colors->identif, data.colors->value);
	//     data.colors = data.colors->next;
	// }

	// int i = 0;
	// printf("----> Map : \n");
	// while (data.map[i])
	// {
	//     printf("%s\n", data.map[i]);
	//     i++;
	// }

	// if (!data.map)
	//     return (printf("ft_split fails!!\n"));
	// data.array = (t_point *)malloc(sizeof(t_point) * data.wnd_wd);
	// if (!data.array)
	//     return (printf("arr allocation!!\n"));
	// if (ft_create_window(&data))
	//     return (-1);
	// data.wall_e =  mlx_load_png("textures/nej.png");
	// data.img_e = mlx_texture_to_image(data.mlx, data.wall_e);

	// data.wall_n =  mlx_load_png("textures/tam.png");
	// data.img_n = mlx_texture_to_image(data.mlx, data.wall_n);

	// data.wall_s =  mlx_load_png("textures/cer.png");
	// data.img_s = mlx_texture_to_image(data.mlx, data.wall_s);

	// data.wall_w =  mlx_load_png("textures/pp.png");
	// data.img_w = mlx_texture_to_image(data.mlx, data.wall_w);

	// ft_set_img(&data);
	// mlx_key_hook(data.mlx, ft_move_plr, &data);
	// ft_mini_map(&data);
	// mlx_loop(data.mlx);
}
