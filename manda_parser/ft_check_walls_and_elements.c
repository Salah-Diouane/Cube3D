/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_walls_and_elements.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:13:12 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:22:56 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/manda_parser.h"

char	*ft_strchr(const char *s, int c)
{
	while ((*s != '\0') && (*s != c))
		s++;
	if (*s == c)
		return ((char *)s);
	return ((char*)NULL);
}

static	int	ft_check_elements(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr("10NSEW ", line[i]))
			i++;
		else
		{
			printf("Invalid character found in the map: %c\n", line[i]);
			return (0);
		}
	}
	return (1);
}

static	char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

int	check_walls_and_elements(char **map)
{
	int		start;
	int		end;
	int		i;
	char	*line;

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
