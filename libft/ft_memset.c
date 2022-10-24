/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:25:10 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:25:11 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Set the first "n" bytes of string "b" with char "c"*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	pos;

	pos = 0;
	while (pos < len)
	{
		((unsigned char *)b)[pos] = (unsigned char)c;
		pos++;
	}
	return ((void *)b);
}
