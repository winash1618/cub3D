/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:24:42 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:24:44 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns String "s" after the first instance of char "c" (inclusive) 
within the first "n" chars. Returns NULL otherwize
**NOT PROTECTED VS NULL INPUT**/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	pos;

	pos = 0;
	c = (unsigned char) c;
	while (pos < n)
	{
		if (((unsigned char *)s)[pos] == c)
			return (&((unsigned char *)s)[pos]);
		pos++;
	}
	return (0);
}
