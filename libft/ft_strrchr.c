/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:26:59 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:27:00 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return the last occurnce of char "c" in string "s" till the end of "s"*/
char	*ft_strrchr(const char *s, int c)
{
	int		pos;

	pos = 0;
	c = (unsigned char) c;
	while (s[pos])
		++pos;
	while (pos >= 0)
	{
		if (s[pos] == c)
			return ((char *)&(s[pos]));
		--pos;
	}
	return (0);
}
