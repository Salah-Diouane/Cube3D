#include "cube.h"

int32_t *ft_get_img_n(mlx_image_t *img)
{
    int32_t *texture;
    int index;
    int pixel_index;

    texture = (int32_t *)malloc(sizeof(int32_t) * (img->width * img->height));
    if (!texture)
        return (NULL);

    int         i;
    int         j;

    i = 0;
    j = 0;
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

int32_t *ft_get_img_s(mlx_image_t *img)
{
    int32_t *texture;
    int index;
    int pixel_index;

    texture = (int32_t *)malloc(sizeof(int32_t) * (img->width * img->height));
    if (!texture)
        return (NULL);

    int         i;
    int         j;

    i = 0;
    j = 0;
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

int32_t *ft_get_img_e(mlx_image_t *img)
{
    int32_t *texture;
    int index;
    int pixel_index;

    texture = (int32_t *)malloc(sizeof(int32_t) * (img->width * img->height));
    if (!texture)
        return (NULL);

    int         i;
    int         j;

    i = 0;
    j = 0;
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

int32_t *ft_get_img_w(mlx_image_t *img)
{
    int32_t *texture;
    int index;
    int pixel_index;

    texture = (int32_t *)malloc(sizeof(int32_t) * (img->width * img->height));
    if (!texture)
        return (NULL);

    int         i;
    int         j;

    i = 0;
    j = 0;
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

void    ft_set_img(t_data  *data)
{
    data->texture_w = ft_get_img_w(data->img);
    data->texture_n = ft_get_img_n(data->img);
    data->texture_s = ft_get_img_s(data->img);
    data->texture_e = ft_get_img_e(data->img);
}

