/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:29:57 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/01 09:38:39 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"



int is_space(unsigned char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int just_space(char *str)
{
	while (*str)
	{
		if (!is_space((unsigned char)*str))
			return -1;
		str++;
	}
	return 0;
}

int is_zero_surrounded_by_ones(char **map, int rows, int cols)
{
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (map[i][j] == '0')
			{
				if (map[i - 1][j] != '1' || map[i + 1][j] != '1' ||
					map[i][j - 1] != '1' || map[i][j + 1] != '1')
					return 0;
			}
		}
	}
	return 1;
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


char *trim_whitespace(char *str)
{
	char *start;
	char *end;
	char *trimmed_str;

	if (just_space(str) != -1)
		return (ft_strdup(""));
	start = str;
	while (is_space((unsigned char)*start))
		start++;
	if (*start == 0)
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && is_space((unsigned char)*end))
		end--;
	end[1] = '\0';
	trimmed_str = ft_strdup(start);
	return (trimmed_str);
}