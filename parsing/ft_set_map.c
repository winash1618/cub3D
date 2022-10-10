/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:40:04 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/10 10:55:53 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_is_linemap(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '1' || tmp[i] == '0' || tmp[i] == ' ' || tmp[i] == 'N'
			|| tmp[i] == 'S' || tmp[i] == 'E' || tmp[i] == 'W')
			i++;
		else
			return (0);
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
t_map	*ft_set_map(int fd, int *err)
{
	(void)fd;
	(void)err;
	char	*line;
	char	*tmp;
	t_map	*map;

	map = NULL;
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, "\n", 1) || ft_spaces(line))
		{
			free(line);
			line = NULL;
			continue ;
		}
		tmp = ft_strtrim(line, "\n");
		if (ft_is_linemap(tmp))
		{
			printf("tmp: [%s]----{%d}\n", tmp, ft_is_linemap(tmp));
		}
		free(tmp);
		free(line);
		line = NULL;
	}
	return(map);
}
/*----------------------------------------------------*/