/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:53:52 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/13 21:12:16 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cube.h"

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
    int         t[2];
    int         b[4];
    int32_t     *pix_arr;
    mlx_image_t *image;

    t[1] = 0;
    t[0] = -1;
    image = load_image(data, path);
    if (!image)
        return (NULL);
    pix_arr = malloc(sizeof(int32_t) * image->width * \
        image->height);
    if (!pix_arr)
        return (NULL);
    while (++t[0] < (image->width * image->height * 4))
    {
        b[0] = image->pixels[t[0]];
        b[1] = image->pixels[t[0]++];
        b[2] = image->pixels[t[0]++];
        b[3] = image->pixels[t[0]++];
        pix_arr[t[1]++] = ((b[1] << 24) | (b[2] << 16) | \
            (b[3] << 8) | b[0]);
    }
    mlx_delete_image(data->mlx, image);
    return (pix_arr);
}
