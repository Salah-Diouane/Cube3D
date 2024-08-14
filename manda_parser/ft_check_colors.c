/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:37:07 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:13:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/manda_parser.h"

int	ft_is_numeric(const char *str)
{
	if (*str == '\0')
		return (1);
	while (*str && *str != '\n')
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

static	int	check_color_args(char **tmp, char **col)
{
	if (tmp[2] != NULL || !tmp[0] || !tmp[1])
		return (printf("COLORS : error more than one argument in texture\n"));
	if (col[0] && col[1] && col[2])
	{
		if (col[0][0] == '\n' || col[1][0] == '\n' || col[2][0] == '\n')
			return (printf("invalid rgb \n"));
		if ((ft_atoi(col[0]) < 0 || ft_atoi(col[0]) > 255) || \
			(ft_atoi(col[1]) < 0 || ft_atoi(col[1]) > 255) || \
			(ft_atoi(col[2]) < 0 || ft_atoi(col[2]) > 255))
			return (printf("invalid rgb \n"));
		if (ft_is_numeric(col[0]) != 0 || ft_is_numeric(col[1]) != 0
			|| ft_is_numeric(col[2]) != 0)
			return (printf("value is not numeric !!!! \n"));
	}
	return (0);
}

static	int	prc_color_line(t_color *colors, char *line, int *c_ct, int *f_ct)
{
	int		result;
	char	**tmp;
	char	**col;
	t_color	*color;

	color = NULL;
	if (!ft_strncmp(line, "C", 1))
		(*c_ct)++;
	else if (!ft_strncmp(line, "F", 1))
		(*f_ct)++;
	tmp = ft_split(line, ' ');
	if (tmp[2])
		return (ft_free_2d(tmp), -1);
	col = ft_split(tmp[1], ',');
	if (!col[1] || ft_get_rows(col) != 3)
		return (ft_free_2d(col), ft_free_2d(tmp), -1);
	result = check_color_args(tmp, col);
	if (result != 0)
		return (ft_free_2d(tmp), ft_free_2d(col), result);
	color = ft_n_clr(tmp[0], ft_atoi(col[0]), ft_atoi(col[1]), ft_atoi(col[2]));
	(ft_free_2d(tmp), ft_free_2d(col));
	if (!color)
		return (printf("Memory allocation failed\n"));
	ft_add_color(&colors, color);
	return (0);
}

static	void	set_colors(t_data *data, t_color *colors)
{
	t_color	*tmp;

	tmp = colors;
	while (tmp)
	{
		if (!ft_strcmp(tmp->identif, "C"))
			data->c_color = (tmp->r << 24) | (tmp->g << 16) | (tmp->b << 8)
				| 255;
		else if (!ft_strcmp(tmp->identif, "F"))
			data->f_color = (tmp->r << 24) | (tmp->g << 16) | (tmp->b << 8)
				| 255;
		tmp = tmp->next;
	}
}

int	ft_get_colors(t_data *data, char **map)
{
	int		i;
	int		c_ct;
	int		f_ct;
	t_color	*colors;

	colors = NULL;
	(1) && (c_ct = 0, f_ct = 0, i = -1);
	while (map[++i])
	{
		map[i][ft_strlen(map[i])] = '\0';
		if (!ft_strncmp(map[i], "C", 1) || !ft_strncmp(map[i], "F", 1))
			if (prc_color_line(colors, map[i], &c_ct, &f_ct))
				return (1);
	}
	set_colors(data, colors);
	free_color(colors);
	if (c_ct != 1 || f_ct != 1)
		return (printf("There must be exactly one 'C' and one 'F'\n"));
	return (0);
}
