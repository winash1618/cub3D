/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:19:21 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 13:23:34 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	valid_line_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] != ' ') && (line[i] != '1') && (line[i] != '0')
			&& (line[i] != 'E') && (line[i] != 'N') && (line[i] != 'S')
			&& (line[i] != 'W'))
			return (0);
		i++;
	}
	if (!empty_space(line) || !all_spaces(line) || !start_end_well(line))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	check_first_last(t_file *file)
{
	t_file	*tmp;
	t_file	*tmp2;
	int		i;

	i = 0;
	tmp = file;
	tmp2 = file;
	while (tmp->line[i])
	{
		if (tmp->line[i] != '1' && tmp->line[i] != ' ')
			return (0);
		i++;
	}
	while (tmp2 && tmp2->next)
		tmp2 = tmp2->next;
	i = 0;
	while (tmp2->line[i])
	{
		if (tmp2->line[i] != '1' && tmp2->line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_space_0(char *str, int i)
{
	if (str[i] && (str[i] == ' ' || str[i - 1] == ' ' || str[i + 1] == ' '))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_space_0_part(char *str, int i)
{
	if (ft_strlen(str) <= i)
		return (0);
	if (str[i] && (str[i] == ' ' || str[i - 1] == ' ' || str[i + 1] == ' '))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	check_zero(t_file *file)
{
	t_file	*tmp;
	int		i;

	tmp = file;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] == '0' || tmp->line[i] == 'N'
				|| tmp->line[i] == 'S' || tmp->line[i] == 'E'
				|| tmp->line[i] == 'W')
			{
				if (tmp && !ft_space_0(tmp->line, i))
					return (0);
				if (tmp && tmp->next && !ft_space_0_part(tmp->next->line, i))
					return (0);
				if (tmp && tmp->prev && !ft_space_0_part(tmp->prev->line, i))
					return (0);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}
/*----------------------------------------------------*/