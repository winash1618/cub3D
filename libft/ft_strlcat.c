/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:26:16 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:26:17 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Concatonate the  chars from string "src" to string "dst"
up to size "dstsize" - 1 and terminate the string>
Return the lenght of the attempted full string length
 **NOT PROTECTD VS NON-NULL TERMINATING STRINGS || NULL INPUT*/
size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	pos;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	pos = ft_strlen(dst);
	if (pos < dstsize)
		len += pos;
	else
		len += dstsize;
	if ((signed)dstsize < 0)
		dstsize = len + pos;
	while ((signed)pos < (signed)(dstsize - 1) && *src)
	{
		dst[pos] = *src;
		src++;
		pos++;
	}
	if (pos == (dstsize - 1) || !(*src))
		dst[pos] = 0;
	return (len);
}
