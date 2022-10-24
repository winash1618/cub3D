/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:40:04 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 08:42:30 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
void	ft_set_helper(int *err, int *i, t_map *map)
{
	if (!(*err))
		*err = ft_check_map(map);
	if (*i != 1)
		*err = 3;
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
// i[3] == is_already_map, start_point, end_map
/*----------------------------------------------------*/
t_map	*ft_set_map(int fd, int *err)
{
	t_map	*map;
	char	*line;
	char	*tmp;
	int		i[3];

	init_ft_set_map(&map, &i[0], &i[1], &i[2]);
	while (1)
	{
		if (ft_no_line(&line, fd, err, &i[2]))
			break ;
		if (!ft_strncmp(line, "\n", 1) || ft_spaces(line))
		{
			if (!ft_map_helper_3(&line, err, &i[0]))
				break ;
			continue ;
		}
		ft_map_helper_2(line, &tmp, &i[2]);
		*err = ft_map_helper_1(&tmp, &i[0], &i[1], &map);
		free(line);
		line = NULL;
	}
	ft_set_helper(err, &(i[1]), map);
	ft_print_map(map);
	return (map);
}
/*----------------------------------------------------*/