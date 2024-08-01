/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:45:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/01 09:52:21 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

int is_space(unsigned char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
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
	end = start + strlen(start) - 1;
	while (end > start && is_space((unsigned char)*end))
		end--;
	end[1] = '\0';
	trimmed_str = ft_strdup(start);
	return (trimmed_str);
}

int ft_first_check_map(t_data *data)
{
	char **cp_map;
	int i = 0, j = 0;

	int rows = ft_get_rows(data->map);
	int cols = ft_get_cols(data->map);

	cp_map = (char **)malloc(sizeof(char *) * (rows + 1));
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
		{
			return (printf("Map is not closed by walls. in |%s| \t %d \n", cp_map[i], i));
		}
	}
	i = 0;
	while (cp_map[i] != NULL)
	{
		if (ft_check_elements(cp_map[i]))
			i++;
		else
		{
			return (printf("error \n"));
		}
	}
	return 0;
}

int ft_second_check_map(t_data *data)
{
	char **cp_map;
	int i = 0, j = 0;

	int rows = ft_get_rows(data->map);
	int cols = ft_get_cols(data->map);

	cp_map = (char **)malloc(sizeof(char *) * (rows + 1));
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
		j = 0;
		while (cp_map[i][j] != '\0')
		{
			if (cp_map[i][j] == '0')
			{
				if (i > 0 && (cp_map[i - 1][j] == ' ' || cp_map[i - 1][j] == '\t' || cp_map[i - 1][j] == '\0'))
				{
					free(cp_map);
					return (printf("invalid_zero_position at %d, %d (above)\n", i, j));
				}
				if (cp_map[i + 1] != NULL && (cp_map[i + 1][j] == ' ' || cp_map[i + 1][j] == '\t' || cp_map[i + 1][j] == '\0'))
				{
					free(cp_map);
					return (printf("invalid_zero_position at %d, %d (below)\n", i, j));
				}
				if (j > 0 && (cp_map[i][j - 1] == ' ' || cp_map[i][j - 1] == '\t' || cp_map[i][j - 1] == '\0'))
				{
					free(cp_map);
					return (printf("invalid_zero_position at %d, %d (left)\n", i, j));
				}
				if (cp_map[i][j + 1] == ' ' || cp_map[i][j + 1] == '\t' || cp_map[i][j + 1] == '\0')
				{
					free(cp_map);
					return (printf("invalid_zero_position at %d, %d (right)\n", i, j));
				}
			}
			j++;
		}
		i++;
	}
	free(cp_map);
	return 0;
}

int ft_check_map(t_data *data)
{
	if ((ft_first_check_map(data) != 0 || ft_second_check_map(data) != 0) && printf("invalid map !!!!!"))
		exit (0);
	return 0;
}
