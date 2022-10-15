/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:35:28 by ayassin           #+#    #+#             */
/*   Updated: 2022/10/15 19:16:10 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns a string copy of the input string s1
**malloc DANGER**/
char	*ft_strdup(const char *s1)
{
	size_t	pos;
	char	*temp;

	pos = 0;
	while (s1[pos])
		pos++;
	temp = (char *)malloc((pos + 1) * sizeof(char));
	if (!temp)
		return (0);
	pos = 0;
	while (s1[pos])
	{
		temp[pos] = s1[pos];
		pos++;
	}
	temp[pos] = 0;
	return (temp);
}
