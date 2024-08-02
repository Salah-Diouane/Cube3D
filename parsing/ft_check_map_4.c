/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:29:57 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/02 08:44:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

double ft_get_direction(char **cp_map, int *i, int *j)
{
	double	angle;

	if (cp_map[*i][*j] == 'N')
		angle = 90 * (M_PI / 180.0);
	else if (cp_map[*i][*j] == 'S')
		angle = 270 * (M_PI / 180.0);
	else if (cp_map[*i][*j] == 'W')
		angle = 180 * (M_PI / 180.0);
	else if (cp_map[*i][*j] == 'E')
		angle = 0 * (M_PI / 180.0);
	return (angle);
}

int just_space(char *str)
{
    while (*str)
    {
        if (!(*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
				|| *str == '\f' || *str == '\r'))
            return (-1);
        str++;
    }
    return (0);
}

int is_all_ones(const char *str)
{
	while (*str)
	{ 
		if (*str != '1')
			return 0;
		str++;
	}
	return 1;
}

int ft_check_elements(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (strchr("10NSEW", line[i]))
			i++;
		else
        {
			printf("Invalid character found in the map:%c\n", line[i]);
            exit (0);
        }
	}
	return (1);
}

char *trim_whitespace(char *str)
{
    char	*start;
    char	*end;
    char	*trimmed_str;

    start = str;
    while (*start)
    {
        if (!(*start == ' ' || *start == '\t' || *start == '\n'
				|| *start == '\v' || *start == '\f' || *start == '\r'))
            break;
        start++;
    }
    if (*start == '\0')
        return (ft_strdup(""));
    start = str;
    while (*start == ' ' || *start == '\t' || *start == '\n'
			|| *start == '\v' || *start == '\f' || *start == '\r')
        start++;
    end = start + ft_strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'
			|| *end == '\v' || *end == '\f' || *end == '\r'))
        end--;
    end[1] = '\0';
    trimmed_str = ft_strdup(start);
    return (trimmed_str);
}

