/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:08:36 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/05 12:09:07 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	*ft_read_line(char *s)
{
	char	*line;
	int		i;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = (char *)g_malloc(i + 1, MALLOC);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_move_string(char *s)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	i += (s[i] == '\n');
	new = (char *)g_malloc(ft_strlen(s) - i + 1, MALLOC);
	if (!new)
		return (NULL);
	j = 0;
	while (s[i + j])
	{
		new[j] = s[i + j];
		j++;
	}
	new[j] = '\0';
	free(s);
	return (new);
}

char	*reader(int fd, char *reserve)
{
	int		rd;
	char	*line;

	line = NULL;
	rd = 1;
	line = (char *)g_malloc((size_t)BUFFER_SIZE + 1, MALLOC);
	if (!line)
		return (NULL);
	while (!(ft_find(reserve, '\n')) && rd != 0)
	{
		rd = read(fd, line, BUFFER_SIZE);
		if (rd < 0)
		{
			free(line);
			free(reserve);
			return (NULL);
		}
		line[rd] = '\0';
		reserve = ft_strjoin(reserve, line);
	}
	free(line);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	reserve = reader(fd, reserve);
	if (!reserve)
	{
		free(reserve);
		return (NULL);
	}
	line = ft_read_line(reserve);
	reserve = ft_move_string(reserve);
	return (line);
}