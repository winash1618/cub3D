/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:24:55 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:24:56 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* copy "n" bytes from "src" to "dst" and return "dst"
**NOT PROTECTED VS NULL INPUT**/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	pos;

	pos = 0;
	if (dst != 0 || src != 0)
	{
		while (pos < n)
		{
			((unsigned char *)dst)[pos] = ((unsigned char *)src)[pos];
			pos++;
		}
	}
	return (dst);
}
