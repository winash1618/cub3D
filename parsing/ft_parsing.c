/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 07:29:21 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/06 14:53:57 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
void	ft_parsing(int ac, char **av)
{
	(void)ac;
	t_parse	*parse;
	int		fd;
	int		err;

	err = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		printf("Error: Invalid file\n");
	parse = (t_parse *)malloc(sizeof(t_parse));
	if (parse == NULL)
		printf("Error: Malloc failed\n");
	parse->info = ft_set_info(fd, &err);
	parse->map = ft_set_map(fd, &err);
	if (err)
		printf("Error: %d Invalid file\n", err);
}
/*----------------------------------------------------*/