/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:33:09 by ayassin           #+#    #+#             */
/*   Updated: 2022/08/05 16:26:26 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the first occurenc of char "c" in string "s" (null inclusive).
Returns NULL otherwise
**NOT PROTECTED VS NULL INPUT**/
char	*ft_strchr(const char *s, int c)
{
	int	pos;

	pos = 0;
	if (!s)
		return (0);
	c = (unsigned char) c;
	while (s[pos])
	{
		if (s[pos] == c)
			return ((char *)&(s[pos]));
		pos++;
	}
	if (s[pos] == c)
		return ((char *)&(s[pos]));
	return (0);
}
