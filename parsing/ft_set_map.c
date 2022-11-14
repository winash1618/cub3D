/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:20:42 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 13:36:38 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	nb_comas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_valid_map(t_file *file)
{
	t_file	*tmp;
	int		pos;

	tmp = file;
	pos = 0;
	while (tmp)
	{
		if (!valid_line_map(tmp->line))
			return (0);
		pos += start_pos(tmp->line);
		tmp = tmp->next;
	}
	if (!check_first_last(file) || !check_zero(file) || pos != 1)
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
t_map	*ft_set_map(t_file *map_file)
{
	t_file	*tmp;
	t_map	*map;

	tmp = map_file;
	map = NULL;
	while (tmp)
	{
		if (!map)
			map = ft_map_new(tmp->line);
		else
			ft_map_add_back(&map, ft_map_new(tmp->line));
		tmp = tmp->next;
	}
	ft_file_clear(&map_file);
	return (map);
}
/*----------------------------------------------------*/
