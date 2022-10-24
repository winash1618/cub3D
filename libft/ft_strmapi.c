/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:26:34 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:26:35 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Apply the function "f" to each char of string "s" to create a new string.
The new string is returned.
**malloc DANGER**/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		pos;
	char	*temp;

	pos = 0;
	if (!s)
		return (0);
	len = ft_strlen(s);
	temp = (char *)malloc((len + 1) * sizeof(char));
	if (!temp)
		return (0);
	while (pos < len)
	{
		temp[pos] = f(pos, s[pos]);
		pos++;
	}
	temp[pos] = 0;
	return (temp);
}
