/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:25:28 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:25:29 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Write integer "n" in file disriptor "fd" (make fd = 1)*/
void	ft_putnbr_fd(int n, int fd)
{
	long	pow10;
	long	clone;
	char	c;

	clone = n;
	pow10 = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		clone *= -1;
	}
	while (clone / (pow10 * 10) != 0)
	{
		pow10 *= 10;
	}
	while (pow10 > 0)
	{
		c = clone / pow10 + '0';
		write(fd, &c, 1);
		clone = clone % pow10;
		pow10 /= 10;
	}
}
