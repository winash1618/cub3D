/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:40:04 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 16:12:31 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/*----------------------------------------------------*/
void	ft_map_helper(char *line, char **tmp, int *end_map)
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
void ft_map_helper_1(char **tmp, int *is_already_map, int *start_point, t_map **map)
{
	*is_already_map = 1;
	*start_point += ft_start_point(*tmp);
	ft_handle_map(map, *tmp);
	free(*tmp);
	*tmp = NULL;
}

int	ft_map_helper_2(char **line, int *err, int *is_already_map)
{
	if (*is_already_map)
		*err = 4;
	free(*line);
	*line = NULL;
	return (1);
}

void init_ft_set_map(t_map **map, char **line, char **tmp)
{
	*map = NULL;
	*line = NULL;
	*tmp = NULL;
	(*map)->is_already_map = 0;
	(*map)->start_point = 0;
	(*map)->end_map = 0;
}
void ft_map_helper_3(char **tmp, t_map **map, int *err)
{
	if (ft_is_linemap(*tmp))
		ft_map_helper_1(tmp, &(*map)->is_already_map, &(*map)->start_point, map);
	else
		ft_map_helper_2(tmp, err, &(*map)->is_already_map);
}
/*----------------------------------------------------*/
t_map	*ft_set_map(int fd, int *err)
{
	t_map	*map;  // start_point, is_already_map, end_map
	t_map	*map2;  // start_point, is_already_map, end_map
	char	*line;
	char	*tmp;
	
	map2 = malloc(sizeof(t_map));
	init_ft_set_map(&map2, &line, &tmp);
	while(1)
	{
		line = get_next_line(fd);
		if (!line && map2->end_map)
			*err = 4;
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, "\n", 1) || ft_spaces(line))
			continue ;
		ft_map_helper(line, &tmp, &map2->end_map);
		ft_map_helper_3(&tmp, &map, err);
		free(line);
		line = NULL;
	}
	*err = ft_check_map(map);
	ft_print_map(map);
	if (map->start_point != 1)
		*err = 3;
	return(map);
}
/*----------------------------------------------------*/
