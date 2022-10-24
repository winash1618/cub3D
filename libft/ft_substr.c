/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:27:13 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:27:14 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return a sub-string of string "s" of length "len" 
starting at char of index "start"
**malloc DANGER**/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	pos;

	pos = 0;
	if (!s)
		return (0);
	if (start < (unsigned int)ft_strlen(s))
		s += start;
	else
		s += ft_strlen(s);
	if (len > (unsigned long)ft_strlen(s))
		len = ft_strlen(s);
	temp = (char *)malloc((len + 1) * sizeof(char));
	if (!temp)
		return (0);
	while (pos < len && *s)
	{
		temp[pos++] = *s;
		s++;
	}
	temp[pos] = 0;
	return (temp);
}
