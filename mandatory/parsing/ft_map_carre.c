/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_carre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:28:59 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/10 03:04:39 by sdiouane         ###   ########.fr       */
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

static char **create_new_map(char **map, int longest_length, int rows)
{
    char    **new_map;
    int     i;
    int     j;
	int     len;

    i = ft_skip_first_spaces(map);
	new_map = (char **)malloc(((rows - i) + 1) * sizeof(char *));
    if (!new_map)
        return (NULL);
    j = 0;
    while (i < rows)
    {
        new_map[j] = (char *)malloc((longest_length + 1) * sizeof(char));
        if (!new_map[j])
            return (ft_free_2d(new_map), NULL);
        ft_strcpy(new_map[j], map[i]);
        len = ft_strlen(new_map[j]);
        while (len < longest_length)
            new_map[j][len++] = ' ';
        new_map[j][longest_length - 1] = '\0';
        j++;
        i++;
    }
    new_map[j] = NULL;
    return (new_map);
}

static char *strip_trailing_whitespace(char *str)
{
    int len;;
    char *result;
    
    len = ft_strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n'))
        len--;
    result = (char *)malloc(len + 1);
    if (result)
    {
        ft_strncpy(result, str, len);
        result[len] = '\0';
    }
    return result;
}

char **ft_new_map(t_data *data, char **map)
{
	int     longest_length;
	int     i;
    char    *tmp;
	char    **new_map;

	longest_length = find_longest_line_length(map);
	i = 0;
    while (map[i])
    {
        tmp = map[i];
        map[i] = strip_trailing_whitespace(tmp);
        if (!map[i])
            return (ft_free_2d(map), NULL);
        free(tmp);
        i++;
    }
	new_map = create_new_map(map, longest_length, ft_get_rows(map));
	if (!new_map)
		return (NULL);
    data->s_map->width = longest_length - 1;
	data->s_map->height = ft_get_rows(new_map);
    ft_free_2d(map);
	return (new_map);
}

int ft_parsing(t_data   *data, char **arv)
{
    if (ft_get_input(data, arv) != 0)
		return (printf("ft_get_input failed !!!!\n"));
	if (ft_check_map(data) != 0)
		return (free_texture(data->text), free_color(data->colors),
            printf("ft_check_map failed !!!!\n"));
    if (set_player_position(data) != 0)
		return (printf("set_position_player failed !!!!\n"));
    return (0);
}
