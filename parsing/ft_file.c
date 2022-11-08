/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:47:26 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/08 17:04:34 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file	*ft_file_new(char *line)
{
	t_file	*file;

	file = NULL;
	file = (t_file *)malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->prev = NULL;
	file->line = ft_strdup(line);
	file->next = NULL;
	return (file);
}

void	ft_file_add_back(t_file **lst, t_file *new)
{
	t_file	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_file_add_front(t_file **lst, t_file *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

void	ft_file_clear(t_file **lst)
{
	t_file	*tmp;

	if (*lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->line);
		free(tmp);
	}
}

void ft_file_print(t_file *lst)
{
	t_file *tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		printf("[%d] {%s}\n", 42, tmp->line);
		tmp = tmp->next;
	}
}
