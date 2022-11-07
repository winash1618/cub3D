/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:44:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/07 20:16:56 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_line_digit(char *line)
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
	return (ft_isdigit(line[i]));
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
t_file	*ft_save_info(t_file *file)
{
	t_file	*tmp;
	t_file	*new_file;

	tmp = file;
	new_file = NULL;
	while (tmp)
	{
		if (ft_line_digit(tmp->line))
			break ;
		if (!new_file)
			new_file = ft_file_new(tmp->line);
		else
			ft_file_add_back(&new_file, ft_file_new(tmp->line));
		tmp = tmp->next;
	}
	return (new_file);
}
/*----------------------------------------------------*/
