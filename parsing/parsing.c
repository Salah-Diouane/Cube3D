/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:19:02 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/24 09:11:53 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

char	**read_map()
{
	char	*line;
	char	*tmp;
	char	**all;
	int 	fd;

	line = NULL;
	fd = open("map.cube", O_RDONLY, 0777);
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (*tmp == '\n' || *tmp == ' ')
		{
			printf("Invalid Map !!");
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
