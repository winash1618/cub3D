/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:27:18 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 12:46:37 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_spaces(char *line)
{
	char	*str;

	str = line;
	while (*str == ' ')
		str++;
	if (!str || !ft_strcmp(str, "\n"))
		return (1);
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
t_file	*ft_save_file(char *str, int *err)
{
	t_file	*file;
	int		fd;
	char	*line;

	file = NULL;
	line = NULL;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		*err = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!file)
			file = ft_file_new(line);
		else
			ft_file_add_back(&file, ft_file_new(line));
		free(line);
	}
	close(fd);
	return (file);
}
/*----------------------------------------------------*/
