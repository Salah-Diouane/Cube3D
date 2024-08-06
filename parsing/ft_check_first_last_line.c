/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_first_last_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:08:31 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/06 15:39:09 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_get_first_index(char *line)
{
    int i = 0;
    while (line && line[i])
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (i);
        i++;
    }
    return (i);
}

int	ft_get_last_index(char *line)
{
    int i = ft_strlen(line) - 1;
    while (line && i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i--;
    return (i);
}

int j_space(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (-1);
        i++;
    }
    return (0);
}

int ft_skip_first_spaces(char **map)
{
    int i = 0;
    while (map[i])
    {
        if (just_space(map[i]) != -1)
            i++;
        else
            break;
    }
    return (i);
}

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

int check_first_last_line(char **map)
{
    int i;
    int start;
    int end;

    if (!map)
        return (-1);
    i = ft_skip_first_spaces(map);
    start = ft_get_first_index(map[i]);
    end = ft_get_last_index(map[i]);
    if (!map[i])
        return (-1);
    while (start <= end)
    {
        if (map[i][start] == '1')
            start++;
        else
            return (printf("First line must be just ones!!!!\n"));
    }
    i = ft_skip_last_spaces(map);
    start = ft_get_first_index(map[i]);
    end = ft_get_last_index(map[i]);
    while (start <= end)
    {
        if (map[i][start] == '1')
            start++;
        else
            return (printf("Last line must be just ones!!!!\n"));
    }
    return 0;
}
