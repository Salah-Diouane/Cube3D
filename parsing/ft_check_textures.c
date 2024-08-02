/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:35:47 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/02 10:11:19 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_text	*ft_new_texture(char *identif, char *chem)
{
	t_text  *new_node;

	new_node = (t_text *)malloc(sizeof(t_text));
	if (!new_node)
		return (NULL);
	new_node->identif = ft_strdup(identif);
	new_node->chem = ft_strdup(chem);
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_texture(t_text **head, t_text *new_node)
{
	t_text  *current;

	if (!head || !new_node)
		return;
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

int ft_count_text_size(t_text *head)
{
    int     count;
    t_text  *current;

    count = 0;
    current = head;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

int ft_get_texture(t_data *data, char **map)
{
	t_text	*txt;
	char	**tmp;
	int		i;

	(1) && (i = 0, txt = NULL, tmp = NULL);
	while (map[i])
	{
		map[i][ft_strlen(map[i])] = '\0';
		if (!strncmp(map[i], "NO", 2) || !strncmp(map[i], "SO", 2) ||
			!strncmp(map[i], "WE", 2) || !strncmp(map[i], "EA", 2))
		{
			tmp = ft_split(map[i], ' ');
			if (tmp[2] != NULL)
				return (printf("TEXTURES : error more than onr args in texture\n"));
			txt = ft_new_texture(tmp[0], tmp[1]);
			if (!txt)
				return (printf("ft_new_texture fails!!\n"));
			ft_add_texture(&data->text, txt);
			free(tmp[0]);
			free(tmp[1]);
			free(tmp);
		}
		i++;
	}
	return (0);
}
