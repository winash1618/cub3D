/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:25:45 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:25:46 by mkaruvan         ###   ########.fr       */
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
