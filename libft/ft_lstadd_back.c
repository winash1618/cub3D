/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:23:30 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:23:31 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* add "wen" node to the end of the "lst"*/
void	ft_lstadd_back(t_list **lst, t_list *wen)
{
	t_list	*temp;

	if (lst)
	{
		temp = *lst;
		if (!(*lst))
		{
			*lst = wen;
			return ;
		}
		while ((*lst)->next != 0)
			*lst = (*lst)->next;
		(*lst)->next = wen;
		*lst = temp;
	}
}
