/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_walls_and_elements.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:13:12 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/08 09:48:50 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static int ft_check_elements(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (strchr("10DNSEW ", line[i]))
            i++;
        else
        {
            printf("Invalid character found in the map: %c\n", line[i]);
            return (0);
        }
    }
    return (1);
}

static char *ft_substr(char *s, int start, int len)
{
    char *temp;
    int i;

    if (s == NULL)
        return (NULL);
    if (start > len)
    {
        if ((temp = malloc(1)) == NULL)
            return (NULL);
        temp[0] = '\0';
        return (temp);
    }
    if ((temp = calloc((len - start + 2), sizeof(char))) == NULL)
        return (NULL);
    i = 0;
    while (start <= len)
    {
        temp[i] = s[start];
        i++;
        start++;
    }
    return (temp);
}

int check_walls_and_elements(char **map)
{
    char *line;
    int start;
    int end;
    int i;

    i = ft_skip_first_spaces(map);
    while (map[i] != NULL)
    {
        start = ft_get_first_index(map[i]);
        end = ft_get_last_index(map[i]);
        if (map[i][start] != '1' || map[i][end] != '1')
            return (printf("Map is not closed by walls at line %d,\n", i + 1));
        line = ft_substr(map[i], start, end);
        if (!ft_check_elements(line))
        {
            free(line);
            return (-1);
        }
        free(line);
        i++;
    }
    return (0);
}
