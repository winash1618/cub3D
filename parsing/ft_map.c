/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:23:17 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/15 12:56:55 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
t_map	*ft_map_new(char *data)
{
	t_map	*new;

	new = (t_map *)malloc(sizeof(t_map));
	if (new == NULL)
		return (NULL);
	new->data = ft_strdup(data);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_map_add_back(t_map **lst, t_map *new)
{
	t_map	*tmp;

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
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_map_add_front(t_map **lst, t_map *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	(*lst)->prev = new;
	*lst = new;
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_map_clear(t_map **lst)
{
	t_map	*tmp;

	if (*lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->data);
		free(tmp);
	}
}
/*----------------------------------------------------*/
/*----------------------------------------------------*/
void	ft_print_map(t_map *lst)
{
	t_map	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		printf("{[%s]}\n", tmp->data);
		tmp = tmp->next;
	}
}
/*----------------------------------------------------*/
