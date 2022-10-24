/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:23:46 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:23:47 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Uses the "del" function on the contents of the "lst" and frees all nodes*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*tempnext;

	if (lst)
	{
		temp = *lst;
		while (temp != 0)
		{
			tempnext = temp -> next;
			if (temp->content)
			{
				del(temp -> content);
				temp->content = NULL;
			}
			free(temp);
			temp = tempnext;
		}
		*lst = 0;
	}
}
