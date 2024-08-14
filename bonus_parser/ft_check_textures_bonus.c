/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_textures_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:35:47 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:43:50 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus_parser.h"

static	void	ft_add_texture(t_data *data, char *identif, char *chem)
{
	if (!ft_strcmp(identif, "NO"))
		data->north_text.path = chem;
	else if (!ft_strcmp(identif, "SO"))
		data->south_text.path = chem;
	else if (!ft_strcmp(identif, "EA"))
		data->east_text.path = chem;
	else if (!ft_strcmp(identif, "WE"))
		data->west_text.path = chem;
}

static	int	process_texture_line(t_data *data, char *line, int *count)
{
	char	**tmp;

	if (!ft_strncmp(line, "NO", 2))
		count[0]++;
	else if (!ft_strncmp(line, "SO", 2))
		count[1]++;
	else if (!ft_strncmp(line, "WE", 2))
		count[2]++;
	else if (!ft_strncmp(line, "EA", 2))
		count[3]++;
	tmp = ft_split(line, ' ');
	if (!tmp)
		return (printf("ft_split in textures fails!!\n"));
	if (tmp[2] != NULL)
		return (ft_free_2d(tmp), printf("more than one argument in texture\n"));
	if (tmp[1][ft_strlen(tmp[1]) - 1] == '\n')
		tmp[1][ft_strlen(tmp[1]) - 1] = '\0';
	ft_add_texture(data, tmp[0], ft_strdup(tmp[1]));
	ft_free_2d(tmp);
	return (0);
}

int	ft_get_texture(t_data *data, char **map)
{
	int				i;
	int				count[4];

	i = 0;
	count[0] = count[1] = count[2] = count[3] = 0;
	while (map[i])
	{
		map[i][ft_strlen(map[i])] = '\0';
		if ((!ft_strncmp(map[i], "NO", 2) || \
			!ft_strncmp(map[i], "SO", 2) || \
			!ft_strncmp(map[i], "WE", 2) || \
			!ft_strncmp(map[i], "EA", 2)) && \
			(process_texture_line(data, map[i], count))) 
				return (1);
		i++;
	}
	if (count[0] != 1 || count[1] != 1 || \
		count[2] != 1 || count[3] != 1)
		return (printf("invalid textures number\n"));
	return (0);
}
