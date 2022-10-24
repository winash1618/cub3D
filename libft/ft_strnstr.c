/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:26:48 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:26:49 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Retun a string since the first occurnce of string "needle" 
in the string "haystack" within "len" chars of "haystack"*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	pos;
	size_t	i;

	pos = 0;
	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[pos] && pos < len)
	{
		while (haystack[pos + i] == needle[i] && (pos + i) < len)
		{
			i++;
			if (!needle[i])
				return ((char *)&(haystack[pos]));
		}
		i = 0;
		pos++;
	}
	return (0);
}
