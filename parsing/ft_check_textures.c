/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:35:47 by sdiouane          #+#    #+#             */
/*   Updated: 2024/08/08 15:16:07 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static t_text	*ft_new_texture(char *identif, char *chem)
{
	t_text  *new_node;

	new_node = (t_text *)malloc(sizeof(t_text));
	if (!new_node)
		return (NULL);
	new_node->identif = ft_strdup(identif);
	if (!new_node->identif)
	{
		free(new_node);
		return (NULL);
	}
	new_node->chem = ft_strdup(chem);
	if (!new_node->chem)
	{
		free(new_node->identif);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

static void	ft_add_texture(t_text **head, t_text *new_node)
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
    while (current && current->next)
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

static int process_texture_line(t_data *data, char *line, t_text_count *count)
{
    char    **tmp;
    t_text  *txt;

    txt = NULL;
    if (!strncmp(line, "NO", 2))
        count->no_count++;
    else if (!strncmp(line, "SO", 2))
        count->so_count++;
    else if (!strncmp(line, "WE", 2))
        count->we_count++;
    else if (!strncmp(line, "EA", 2))
        count->ea_count++;
    tmp = ft_split(line, ' ');
    if (!tmp)
        return (printf("ft_split in textures fails!!\n"));
    if (tmp[2] != NULL)
        return (ft_free_2d(tmp), printf("more than one argument in texture\n"));
    if (tmp[1][ft_strlen(tmp[1]) - 1] == '\n')
        tmp[1][ft_strlen(tmp[1]) - 1] = '\0';
    txt = ft_new_texture(tmp[0], tmp[1]);
    if (!txt)
        return (ft_free_2d(tmp), printf("ft_new_texture fails!!\n"));
    ft_free_2d(tmp);
    ft_add_texture(&data->text, txt);
    return (0);
}
int ft_get_texture(t_data *data, char **map)
{
    int i;
    t_text_count count;

    count.ea_count = 0;
    count.we_count = 0;
    count.no_count = 0;
    count.so_count = 0;
    i = 0;
    while (map[i])
    {
        map[i][ft_strlen(map[i])] = '\0';
        if (!strncmp(map[i], "NO", 2) || !strncmp(map[i], "SO", 2) ||
            !strncmp(map[i], "WE", 2) || !strncmp(map[i], "EA", 2))
        {
            if (process_texture_line(data, map[i], &count))
                return (1);
        }
        i++;
    }
    if (count.no_count != 1 || count.so_count != 1 || 
        count.we_count != 1 || count.ea_count != 1)
        return (printf("There must be exactly one 'NO', 'SO', 'WE', and 'EA'\n"));
    return (0);
}

