/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:20:42 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/07 20:25:44 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
t_file	*ft_save_map(t_file *file)
{
	t_file *tmp;
	t_file *new_file;

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
