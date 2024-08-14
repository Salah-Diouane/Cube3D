/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:55:19 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/13 21:11:29 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cube.h"

void    free_2d_arr(char **arr)
{
    int     i;

    i = -1;
    while (arr && arr[++i])
        free (arr[1]);
    free(arr);
}

void    free_lnkd_lst(t_face *lst)
{
    t_face      *tmp;
    
    while (lst && lst->next)
    {
        tmp = lst;
        lst = lst->next;
        free (tmp);
    }
}

void    free_map_text(t_data *data)
{
    free(data->north_text.path);
    free(data->south_text.path);
    free(data->west_text.path);
    free(data->east_text.path);
    free_2d_arr(data->map.arr);
}

void    clean_up(t_data *data)
{
    free_map_text(data);
    free(data->inter_arr);
    mlx_delete_image(data->mlx, data->proj_img);
    mlx_terminate(data->mlx);
    free_lnkd_lst(data->face_lst);
    exit(0);
}