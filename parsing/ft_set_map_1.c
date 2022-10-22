/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:04:42 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 14:06:09 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_is_valid_end(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_space_0(char *str, char *str1, char *str2, int i)
{
	if (str[i - 1] == ' ' || str[i + 1] == ' ')
		return (0);
	if (str1[i - 1] == ' ' || str1[i] == ' ' || str1[i + 1] == ' ')
		return (0);
	if (str2[i - 1] == ' ' || str2[i] == ' ' || str2[i + 1] == ' ')
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_data2(char *str, char *str1, char *str2)
{
	if (str[0] == '0' || str1[0] == '0' || str2[0] == '0')
		return (0);
	if (str[ft_strlen(str) - 1] == '0'
		|| str1[ft_strlen(str1) - 1] == '0'
		|| str2[ft_strlen(str2) - 1] == '0')
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_data(t_map *line, t_map *line1, t_map *line2)
{
	int	i;

	i = 0;
	if (!line1)
		return (0);
	if (!line2)
	{
		if (!ft_is_valid_end(line->data))
			return (1);
	}
	if (line1 && line2)
	{
		if (!ft_check_data2(line->data, line1->data, line2->data))
			return (1);
		while (line->data[i])
		{
			if (line->data[i] == '0')
			{
				if (!ft_space_0(line->data, line1->data, line2->data, i))
					return (1);
			}
			i++;
		}
	}
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_map(t_map *map)
{
	t_map	*tmp;
	t_map	*line1;
	t_map	*line2;

	tmp = map;
	line1 = NULL;
	line2 = NULL;
	while (tmp != NULL)
	{
		if (tmp)
		{
			line1 = tmp->prev;
			line2 = tmp->next;
			if (ft_check_data(tmp, line1, line2))
				return (5);
		}
		tmp = tmp->next;
	}
	return (0);
}
/*----------------------------------------------------*/
