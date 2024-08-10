/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:37:07 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/10 02:54:37 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int ft_is_numeric(const char *str)
{
    if (*str == '\0')
        return (1);
    while (*str && *str != '\n')
    {
        if (*str < '0' || *str > '9')
            return (1);
        str++;
    }
    return (0);
}

static int check_color_args(char **tmp, char **col)
{
    if (tmp[2] != NULL || !tmp[0] || !tmp[1])
        return (printf("COLORS : error more than one argument in texture\n"));

    if (col[0] && col[1] && col[2])
    {
        if (col[0][0] == '\n' || col[1][0] == '\n' || col[2][0] == '\n')
            return (printf("invalid rgb \n"));
        if ((ft_atoi(col[0]) < 0 || ft_atoi(col[0]) > 255) ||
            (ft_atoi(col[1]) < 0 || ft_atoi(col[1]) > 255) ||
            (ft_atoi(col[2]) < 0 || ft_atoi(col[2]) > 255))
            return (printf("invalid rgb \n"));
        if (ft_is_numeric(col[0]) != 0 || ft_is_numeric(col[1]) != 0
            || ft_is_numeric(col[2]) != 0)
            return (printf("value is not numeric !!!! \n"));
    }
    return (0);
}

static t_color *create_color(char **tmp, char **col)
{
    return (ft_new_color(tmp[0], ft_atoi(col[0]), ft_atoi(col[1]), ft_atoi(col[2])));
}

static int process_color_line(t_data *data, char *line, int *c_count, int *f_count)
{
    char **tmp;
    char **col;
    t_color *color = NULL;
    int result;

    if (!strncmp(line, "C", 1))
        (*c_count)++;
    else if (!strncmp(line, "F", 1))
        (*f_count)++;
    tmp = ft_split(line, ' ');
    if (tmp[2])
        return (ft_free_2d(tmp), -1);
    col = ft_split(tmp[1], ',');
    if (!col[1])
        return (ft_free_2d(col), ft_free_2d(tmp), -1);
    result = check_color_args(tmp, col);
    if (result != 0)
    {
        ft_free_2d(tmp);
        ft_free_2d(col);
        return result;
    }
    color = create_color(tmp, col);
    ft_free_2d(tmp);
    ft_free_2d(col);
    if (!color)
        return (printf("Memory allocation failed\n"));
    ft_add_color(&data->colors, color);
    return (0);
}

int ft_get_colors(t_data *data, char **map)
{
    int i;
    int c_count;
    int f_count;

    c_count = 0;
    f_count = 0;
    i = 0;
    while (map[i])
    {
        map[i][strlen(map[i])] = '\0';
        if (!strncmp(map[i], "C", 1) || !strncmp(map[i], "F", 1))
        {
            if (process_color_line(data, map[i], &c_count, &f_count))
                return (1);
        }
        i++;
    }
    if (c_count != 1 || f_count != 1)
        return (printf("There must be exactly one 'C' and one 'F'\n"));
    return (0);
}
