/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_carre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:28:59 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/06 16:30:14 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static int find_longest_line_length(char **map)
{
	int longest_length = 0;
	int length;
	int i = 0;

	while (map[i] != NULL)
	{
		length = strlen(map[i]);
		if (length > longest_length)
		{
			longest_length = length;
		}
		i++;
	}
	return longest_length;
}

static char	*ft_strcpy(char *dest,  char *src)
{
    char	*dest_start;
	
	dest_start = dest;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return (dest_start);
}

static char **create_new_map(char **map, int longest_length, int rows)
{
    char **new_map;
    int i;
	int len;

	new_map = (char **)malloc((rows + 1) * sizeof(char *));
	i = 0;
    if (!new_map)
        return (NULL);
    while (i < rows)
    {
        new_map[i] = (char *)malloc((longest_length + 1) * sizeof(char));
        if (!new_map[i])
        {
            while (--i >= 0)
                free(new_map[i]);
            free(new_map);
            return (NULL);
        }
        ft_strcpy(new_map[i], map[i]);
        len = ft_strlen(new_map[i]);
        while (len < longest_length)
            new_map[i][len++] = ' ';
        new_map[i][longest_length] = '\0';
        i++;
    }
    new_map[rows] = NULL;
    return (new_map);
}

static char *strip_trailing_whitespace(const char *str)
{
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n'))
    {
        len--;
    }
    char *result = (char *)malloc(len + 1);
    if (result)
    {
        strncpy(result, str, len);
        result[len] = '\0';
    }
    return result;
}

char **ft_new_map(char **map)
{
	char **new_map;
	int longest_length;
	int	i;

	longest_length = find_longest_line_length(map);
	i = 0;
    while (map[i])
    {
        map[i] = strip_trailing_whitespace(map[i]);
        i++;
    }
	new_map = create_new_map(map, longest_length, ft_get_rows(map));
	if (!new_map)
		return (NULL);
	return (new_map);
}
