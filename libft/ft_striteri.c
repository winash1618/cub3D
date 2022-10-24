/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:26:01 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:26:02 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Apply function "f" to each char of string "s"*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	pos;

	pos = 0;
	if (s)
	{
		while (s[pos])
		{
			f(pos, &(s[pos]));
			pos++;
		}
	}
}
