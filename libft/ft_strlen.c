/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:26:26 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:26:27 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return int length of string "s1"
**NOT PROTECTED VS NULL INPUT**/
int	ft_strlen(const char *s)
{
	int	len;

	if (s == NULL)
		return (0);
	len = -1;
	while (s[++len])
		;
	return (len);
}
