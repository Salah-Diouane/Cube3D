#include "cube.h"

static int32_t *ft_get_img(mlx_image_t *img)
{
    int         i;
    int         j;
    int32_t     *texture;

    i = 0;
    j = 0;
    texture = (int32_t *)malloc(sizeof(int32_t) * (img->width * img->height));
    if (!texture)
        return (NULL);
    while (i < (img->width * img->height * 4))
    {
        int b1 = img->pixels[i];
        int b2 = img->pixels[i + 1];
        int b3 = img->pixels[i + 2];
        int b4 = img->pixels[i + 3];
        texture[j] =  (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
        i += 4;
        j++;
    }
    return (texture);
}

static void	png_check(t_data *data, char *map)
{
	if (strstr(map, ".png") == 0
		&& printf("Format should be '.png'\n"))
    {
        free_map(data->s_map);
        free_color(data->colors);
        free_texture(data->text);
		exit(EXIT_FAILURE);
    }
}

int validate_png_filename( char *filename)
{
    const char *dot = strrchr(filename, '.');
    int i = 0;
    while (filename[i] != '.')
        i++;
    if (!dot || dot == filename)
        return 0;
    if (filename[i - 1] == '/')
        return 0;
    if (strcmp(dot, ".png") != 0)
        return 0;
    if (strstr(filename, ".png") != dot)
        return 0;

    return 1;
}

void    ft_set_img(t_data  *data)
{
    mlx_image_t     *image;
    mlx_texture_t   *texture;
    t_text          *tmp;

    tmp = data->text;
    while (tmp)
    {
        if (!validate_png_filename(tmp->chem))
        {
            printf("Format should be '.png'\n");
            free_map(data->s_map);
            free_color(data->colors);
            free_texture(data->text);
            exit(EXIT_FAILURE);           
        }
        texture =  mlx_load_png(tmp->chem);
        if (!texture)
        {
            free_map(data->s_map);
            free_color(data->colors);
            free_texture(data->text);
            exit(EXIT_FAILURE);           
        }
        image = mlx_texture_to_image(data->mlx, texture);
        if (!strcmp(tmp->identif, "NO"))
        {
            tmp->pix_arr = ft_get_img(image);
            data->arr_pxl_n = tmp->pix_arr;
        }
        if (!strcmp(tmp->identif, "SO"))
        {
            tmp->pix_arr = ft_get_img(image);
            data->arr_pxl_s = tmp->pix_arr;
        }
        if (!strcmp(tmp->identif, "WE"))
        {
            tmp->pix_arr = ft_get_img(image);
            data->arr_pxl_w = tmp->pix_arr;
        }
        if (!strcmp(tmp->identif, "EA"))
        {
            tmp->pix_arr = ft_get_img(image);
            data->arr_pxl_e = tmp->pix_arr;
        }
        tmp = tmp->next;
    }
    texture =  mlx_load_png("textures/door.png");
    image = mlx_texture_to_image(data->mlx, texture);
    data->d_text.tb = ft_get_img(image);
}
