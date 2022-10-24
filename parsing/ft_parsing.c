/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 07:29:21 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 09:41:01 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
void	ft_parse_clear(t_parse **parse)
{
	if (!parse || !*parse)
		return ;
	if ((*parse)->map)
		ft_map_clear(&(*parse)->map);
	if ((*parse)->info)
		ft_info_clear(&(*parse)->info);
	free(*parse);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_av(char *str)
{
	if (!ft_strcmp(ft_strrchr(str, '.'), ".cub"))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_parsing(int ac, char **av, t_parse **parse)
{
	int	fd;
	int	err;

	err = 0;
	if (ac == 1 || ac > 2)
		return (7);
	if (ft_check_av(av[1]))
		return (6);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	*parse = (t_parse *)malloc(sizeof(t_parse));
	(*parse)->info = ft_set_info(fd, &err);
	if (err)
		return (err);
	close(fd);
	fd = open(av[1], O_RDONLY);
	(*parse)->map = ft_set_map(fd, &err);
	close(fd);
	if (!(*parse)->info || !(*parse)->map || ft_info_len((*parse)->info) != 6)
		return (1);
	return (err);
}
/*----------------------------------------------------*/