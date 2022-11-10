/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:17:26 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 13:17:39 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	start_pos(char *str)
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
t_file	*ft_save_map(t_file *file)
{
	t_file	*tmp;
	t_file	*new_file;

	tmp = file;
	new_file = NULL;
	while (tmp)
	{
		if (ft_line_digit(tmp->line))
		{
			while (tmp)
			{
				if (!new_file)
					new_file = ft_file_new(tmp->line);
				else
					ft_file_add_back(&new_file, ft_file_new(tmp->line));
				tmp = tmp->next;
			}
		}
		else
			tmp = tmp->next;
	}
	return (new_file);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	empty_space(char *str)
{
	if (ft_strlen(str) == 0)
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	all_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
			return (1);
	}
	if (!line[i])
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	start_end_well(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
			break ;
	}
	if (line[i] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	return (1);
}
/*----------------------------------------------------*/