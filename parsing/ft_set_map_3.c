/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:20:50 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 08:43:02 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
void	ft_map_helper_2(char *line, char **tmp, int *end_map)
{
	if (there_is_new_line(line))
	{
		*tmp = ft_strtrim(line, "\n");
		*end_map = 1;
	}
	else
	{
		*tmp = ft_strdup(line);
		*end_map = 0;
	}
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_map_helper_1(char **tmp, int *is_already_map, int *start_point,
		t_map **map)
{
	int	err;

	err = 0;
	if (ft_is_linemap(*tmp))
	{
		*is_already_map = 1;
		*start_point += ft_start_point(*tmp);
		ft_handle_map(map, *tmp);
		free(*tmp);
		*tmp = NULL;
	}
	else if (*is_already_map)
	{
		err = 4;
		free(*tmp);
		*tmp = NULL;
	}
	else
	{
		free(*tmp);
		*tmp = NULL;
	}
	return (err);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_no_line(char **line, int fd, int *err, int *end_map)
{
	*line = get_next_line(fd);
	if (!*line && *end_map)
		*err = 4;
	if (*line == NULL)
		return (1);
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_map_helper_3(char **line, int *err, int *is_already_map)
{
	if (*is_already_map)
	{
		*err = 4;
		free(*line);
		*line = NULL;
		return (0);
	}
	free(*line);
	*line = NULL;
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	init_ft_set_map(t_map **map, int *is_already_map, int *start_point,
		int *end_map)
{
	*map = NULL;
	*is_already_map = 0;
	*start_point = 0;
	*end_map = 0;
}
/*----------------------------------------------------*/