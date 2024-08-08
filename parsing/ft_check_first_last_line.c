/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_first_last_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:08:31 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/08 15:21:16 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int ft_skip_last_spaces(char **map)
{
    int i = 0;
    while (map[i])
        i++;
    i--;
    while (i >= 0)
    {
        if (just_space(map[i]) != -1)
            i--;
        else
            break;
    }
    return (i);
}

static int check_line_content(char *line, int start, int end, 
    const char *error_message)
{
    while (start <= end)
    {
        if (line[start] == '1' || line[start] == ' ' || line[start] == '\t')
            start++;
        else
            return (printf("%s\n", error_message));
    }
    return 0;
}

static int check_first_last_line_content(char **map, int (*skip_func)(char **),
    const char *error_message)
{
    int i;
    int start;
    int end;

    if (!map)
        return (-1);
    i = skip_func(map);
    if (!map[i])
        return (-1);
    start = ft_get_first_index(map[i]);
    end = ft_get_last_index(map[i]);
    return (check_line_content(map[i], start, end, error_message));
}

int check_first_last_line(char **map)
{
    int result;

    result = check_first_last_line_content(map, ft_skip_first_spaces,
        "First line must be just ones!!!!");
    if (result != 0)
        return (result);
    result = check_first_last_line_content(map, ft_skip_last_spaces,
        "Last line must be just ones!!!!");
    return (result);
}

