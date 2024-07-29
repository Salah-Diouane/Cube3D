/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:07:16 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/29 08:07:31 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	**read_map(int fd)
{
	char	*line;
	char	*tmp;
	char	**all;

	line = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (*tmp == '\n' || *tmp == ' ')
		{
			ft_printf("Invalid Map !!");
			exit(EXIT_FAILURE);
		}
		line = ft_strjoin(line, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	all = ft_split(line, '\n');
	free(line);
	return (all);
}
