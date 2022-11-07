/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:17:14 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/07 20:27:12 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_parsing(int ac, char **av)
{
	(void)	ac;
	int		err;
	t_file	*file;
	t_file	*info_file;
	t_file	*map_file;

	err = 0;
	file = ft_save_file(av[1], &err);
	if (err)
		printf("Error...\n");
	file = ft_clean_file(file);
	ft_file_print(file);
	printf("--------------INFO_FILE\n");
	info_file = ft_save_info(file);
	ft_file_print(info_file);
	ft_file_clear(&info_file);
	printf("--------------MAP_FILE\n");
	map_file = ft_save_map(file);
	ft_file_print(map_file);
	ft_file_clear(&map_file);
	
	ft_file_clear(&file);
}
