/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:07:42 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 14:11:48 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
void	ft_handle_map(t_map **map, char *tmp)
{
	if (!*map)
		*map = ft_map_new(tmp);
	else
		ft_map_add_back(map, ft_map_new(tmp));
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	there_is_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_is_begmap(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] == ' ')
		i++;
	if (ft_isdigit(tmp[i]))
		return (1);
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_start_point(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			count++;
		i++;
	}
	return (count);
}
/*----------------------------------------------------*/

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