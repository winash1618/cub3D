/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:14:55 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/06 23:50:08 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
t_info	*ft_info_new(char *data, enum e_type type)
{
	t_info	*new;

	new = (t_info *)malloc(sizeof(t_info));
	if (new == NULL)
		return (NULL);
	new->data = data;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_info_add_back(t_info **lst, t_info *new)
{
	t_info	*tmp;

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
void	ft_info_add_front(t_info **lst, t_info *new)
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
void	ft_info_clear(t_info **lst)
{
	t_info	*tmp;

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
void	ft_print_info(t_info *lst)
{
	t_info *tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		printf("{[%s], %d}\n", tmp->data, tmp->type);
		tmp = tmp->next;
	}
}
/*----------------------------------------------------*/
