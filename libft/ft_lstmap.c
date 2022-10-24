/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:24:22 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:24:23 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return a new list that f(lst -> content) as conent.
Returns NULL & "del" the content of new list if the "lst" has NULL content
**malloc DANGER**/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nwlst;

	if (!lst)
		return (NULL);
	nwlst = NULL;
	while (lst)
	{
		if ((lst->content) == NULL)
		{
			ft_lstclear(&nwlst, del);
			return (NULL);
		}
		ft_lstadd_back(&nwlst, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (nwlst);
}
