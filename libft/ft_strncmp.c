/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:26:41 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:26:42 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compare the first "n" chars from strings "s1" & "s2".
Return the diffrence in the first char or 0 if no diffrence is found
**NOT PROTECTED VS NULL INPUT**/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	if (!n)
		return (0);
	while (pos < (n - 1) && s1[pos] && s2[pos] && (unsigned char)s1[pos]
		== (unsigned char)s2[pos])
		pos++;
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}
