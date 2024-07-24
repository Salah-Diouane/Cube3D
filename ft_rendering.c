# include "cube.h"

void    ft_render_wall(t_data *data, double dst, int x)
{
    double      y;
    double      end;
    double      height;

    height = (300 * 50) / dst;
    y = (data->wd_ht / 2) - (height / 2);
    end = (data->wd_ht / 2) + (height / 2);
    while (y < end)
    {
        if (0 < y && y < data->wd_ht)
            mlx_put_pixel(data->ddd__img, \
                x, y, 0x00FFFF);
        y++;
    }
}
