/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:22:05 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:22:08 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* returns allocated memory for "count" objects each with "size" bytes 
**malloc DANGER* */
void	*ft_calloc(size_t count, size_t size)
{
	void	*x;
	size_t	i;
	size_t	j;
	size_t	pos;

	pos = 0;
	i = 0;
	x = (void *)malloc(count * size * sizeof(unsigned char));
	if (!x)
		return (0);
	while (i < count)
	{
		j = 0;
		while (j < size)
		{
			((unsigned char *)x)[pos] = 0;
			pos++;
			j++;
		}
		i++;
	}
	return (x);
}
