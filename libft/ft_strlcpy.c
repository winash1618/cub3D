/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:26:21 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:26:22 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Copy from string "src" to overwrite "dst" till "dstsize" - 1 and terminate
Return the length of "src" or 0 for "dstsize = 0"*/
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	pos;
	size_t	len;

	pos = 0;
	while (src[pos])
		pos++;
	if (dstsize == 0)
		return (pos);
	len = pos;
	pos = 0;
	while (pos < (dstsize - 1) && src[pos])
	{
		dst[pos] = src[pos];
		pos++;
	}
	dst[pos] = 0;
	return (len);
}
