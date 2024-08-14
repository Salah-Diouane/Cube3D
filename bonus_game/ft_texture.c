# include "../include/bonus.h"

void    free_textures(t_data *data, int set)
{
    if (1 <= set)
        free (data->north_text.arr);
    if (2 <= set)
        free (data->south_text.arr);
    if (3 <= set)
        free (data->west_text.arr);
    if (4 <= set)
        free (data->east_text.arr);
    if (5 <= set)
        free (data->door_text.arr);
}

mlx_image_t *load_image(t_data *data, char *path)
{
    mlx_image_t         *image;
    mlx_texture_t       *texture;

    texture = mlx_load_png(path);
    if (!texture)
        return (NULL);
    image = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    return (image);
}

int32_t *get_texture_arr(t_data *data, char *path)
{
    int         i;
    int         j;
    int         byte[4];
    int32_t     *pix_arr;
    mlx_image_t *image;

    j = 0;
    i = 0;
    image = load_image(data, path);
    if (!image)
        return (NULL);
    pix_arr = malloc(sizeof(int32_t) * image->width * \
        image->height);
    if (!pix_arr)
        return (NULL);
    while (i < (image->width * image->height * 4))
    {
        byte[0] = image->pixels[i + 0];
        byte[1] = image->pixels[i + 1];
        byte[2] = image->pixels[i + 2];
        byte[3] = image->pixels[i + 3];
        pix_arr[j++] = ((byte[0] << 24) | \
            (byte[1] << 16) | (byte[2] << 8) | byte[3]);
        i += 4;
    }
    mlx_delete_image(data->mlx, image);
    return (pix_arr);
}