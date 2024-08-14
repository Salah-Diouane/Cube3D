/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_carre_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:27:45 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/13 21:13:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/manda_parser.h"

static int	cmp_char(char c1, char c2)
{
	if (c1 != c2)
		return (c1 - c2);
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int			i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (cmp_char(s1[i], s2[i]))
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
		return (cmp_char(s1[i], s2[i]));
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcpy(char	*dest, char	*src)
{
	char	*dest_start;

	dest_start = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_start);
}

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
