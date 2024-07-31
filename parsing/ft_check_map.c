/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:45:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/31 15:39:05 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"
#include <ctype.h>

int just_space(char *line)
{
	int i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		{
			i++;
		}
		else
		{
			return (-1);
		}
	}
	return (0);
}

int ft_check_content(char *line)
{
	int i = 0;

	while (line && line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' ||
			line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || line[i] == '\n')
		{
			i++;
		}
		else
		{
			return (-1);
		}
	}
	return (0);
}

int ft_get_rows(char **map)
{
	int rows = 0;
	while (map[rows])
	{
		rows++;
	}
	return rows;
}

int find_longest_line(char **map)
{
	int longest_length;
	int longest_index;
	int length;
	int rows;
	int i;

	i = 0;
	longest_length = 0;
	longest_index = -1;
	rows = ft_get_rows(map);
	while (i < rows)
	{
		length = ft_strlen(map[i]);
		if (length > longest_length)
		{
			longest_length = length;
			longest_index = i;
		}
		i++;
	}
	return (longest_index);
}

int ft_get_cols(char **map)
{
	return strlen(map[0]);
}

int is_closed_by_walls(char **map, int rows, int cols)
{
	for (int j = 0; j < cols; j++)
	{
		if (map[0][j] != '1' || map[rows - 1][j] != '1')
		{
			return 0;
		}
	}

	for (int i = 0; i < rows; i++)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
		{
			return 0;
		}
	}

	return 1;
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
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

char *trim_whitespace(char *str)
{
	char *end;
	char *trimmed_str;

	// Copy the original string to avoid modifying the input string directly
	if (just_space(str) != -1)
		return (str);
	trimmed_str = strdup(str);
	if (trimmed_str == NULL)
		return NULL;

	// Trim leading space
	while (isspace((unsigned char)*trimmed_str))
		trimmed_str++;

	if (*trimmed_str == 0)
	{ // All spaces?
		free(trimmed_str);
		return strdup(""); // Return an empty string
	}

	// Trim trailing space
	end = trimmed_str + strlen(trimmed_str) - 1;
	while (end > trimmed_str && isspace((unsigned char)*end))
		end--;

	// Write new null terminator character
	end[1] = '\0';

	// Duplicate the trimmed string to return it, freeing the intermediate copy
	char *result = strdup(trimmed_str);
	free(trimmed_str - (trimmed_str - str)); // Free the original duplicated string
	return result;
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
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			i++;
		else
			return (printf("Invalid character found in the map: %c\n", line[i]));
	}
	return (1);
}

int ft_check_map(t_data *data)
{
	char **cp_map;
	int i = 0, j = 0;

	int rows = ft_get_rows(data->map);
	int cols = ft_get_cols(data->map);

	cp_map = (char **)malloc(sizeof(char *) * (find_longest_line(data->map) + 1));
	if (!cp_map)
		return (printf("mall err\n"));

	while (data->map[i])
	{
		if (just_space(data->map[i]) != -1)
			i++;
		else
			break;
	}

	while (data->map[i])
	{
		cp_map[j] = trim_whitespace(data->map[i]);
		if (cp_map[j] == NULL)
		{
			for (int k = 0; k < j; k++)
				free(cp_map[k]);
			free(cp_map);
			return (printf("Memory allocation error.\n"));
		}
		j++;
		i++;
	}
	cp_map[j] = NULL;

	if (!is_all_ones(cp_map[0]) || !is_all_ones(cp_map[j - 1]))
	{
		for (int k = 0; k < j; k++)
			free(cp_map[k]);
		free(cp_map);
		return (printf("The first or last line is not all ones.\n"));
	}

	i = 0;
	while (cp_map[i] && cp_map[i][0])
	{
		if (cp_map[i][0] == '1' && cp_map[i][strlen(cp_map[i]) - 1] == '1')
			i++;
		else
			return (printf("Map is not closed by walls. in |%s| \t %d \n", cp_map[i], i));
	}
	i = 0;
	while (cp_map[i] != NULL)
	{
		if (ft_check_elements(cp_map[i]))
			i++;
		else
			return (printf("error \n"));
	}
	for (int k = 0; k < j; k++)
		free(cp_map[k]);
	free(cp_map);
	return 0;
}

int is_invalid_zero_position(char **map, int current_line, int col)
{
	if (col < 0 || col >= strlen(map[current_line]))
		return 1;
	if (map[current_line][col] == ' ' || map[current_line][col] == '\t' || map[current_line][col] == '\0')
		return 1;
	return 0;
}

int ft_second_check_map(t_data *data)
{
	char **cp_map;
	int i = 0, j = 0;

	int rows = ft_get_rows(data->map);
	int cols = ft_get_cols(data->map);

	cp_map = (char **)malloc(sizeof(char *) * (find_longest_line(data->map) + 1));
	if (!cp_map)
		return (printf("mall err\n"));

	while (data->map[i])
	{
		if (just_space(data->map[i]) != -1)
			i++;
		else
			break;
	}
	while (data->map[i])
	{
		cp_map[j] = data->map[i];
		if (cp_map[j] == NULL)
		{
			for (int k = 0; k < j; k++)
				free(cp_map[k]);
			free(cp_map);
			return (printf("Memory allocation error.\n"));
		}
		j++;
		i++;
	}
	cp_map[j] = NULL;
	i = 0;
	while (cp_map[i] != NULL)
	{
		printf("cp_map[%d] : %s\n", i, cp_map[i]);
		j = 0;
		while (cp_map[i][j] != '\0')
		{
			if (cp_map[i][j] == '0')
			{
				
			}
			j++;
		}
		i++;
	}
	for (int k = 0; k < j; k++)
		free(cp_map[k]);
	cp_map = NULL;
	free(cp_map);
	return 0;
}
