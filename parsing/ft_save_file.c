/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:27:18 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/03 21:53:05 by mkaruvan         ###   ########.fr       */
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
int	ft_get_type(char *line)
{
	(void)	line;
	int		type;

	type = 0;

	return (type);
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
	if(fd == -1)
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
