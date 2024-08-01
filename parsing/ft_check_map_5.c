/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:34:29 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/01 12:09:50 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int ft_check_elements(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (strchr("10NSEW", line[i]))
		{
			i++;
		}
		else
        {
			printf("Invalid character found in the map:%c\n", line[i]);
            exit (0);
        }
	}
	return (1);
}

