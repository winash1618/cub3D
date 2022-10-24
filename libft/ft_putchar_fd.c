/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 07:25:16 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 07:25:17 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* write char "c" in output in file discriptor "fd" (make fd =1)*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
