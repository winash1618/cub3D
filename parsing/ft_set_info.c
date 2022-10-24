/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:39:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 19:54:01 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
t_info	*ft_set_info(int fd, int *err)
{
	t_info	*info;
	char	*line;

	info = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, "\n", 1) || ft_spaces(line))
		{
			free(line);
			continue ;
		}
		if (ft_is_map(line, err))
		{
			free(line);
			break ;
		}
		ft_handle_info(line, &info, err);
		free(line);
	}
	ft_print_info(info);
	return (info);
}
/*----------------------------------------------------*/
