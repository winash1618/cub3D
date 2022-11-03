/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:17:14 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/03 22:19:46 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_parsing(int ac, char **av)
{
	(void)	ac;
	int		err;
	t_file	*file;

	err = 0;
	file = ft_save_file(av[1], &err);
	if (err)
		printf("Error...\n");
	file = ft_clean_file(file);
	ft_file_print(file);
	ft_file_clear(&file);
}
