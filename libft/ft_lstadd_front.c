/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:23:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:23:40 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Add node "wen" to the fron of "lst"*/
void	ft_lstadd_front(t_list **lst, t_list *wen)
{
	wen -> next = *lst;
	*lst = wen;
}
