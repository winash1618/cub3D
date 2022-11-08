/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:39:34 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/08 11:33:32 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
t_file	*ft_clean_file(t_file *file)
{
	t_file	*tmp;
	t_file	*new_file;
	char	*line;
	int		is_already_map;

	is_already_map = 0;
	new_file = NULL;
	tmp = file;
	while (tmp)
	{
		if ((!ft_strcmp(tmp->line, "\n") || ft_spaces(tmp->line))
			&& !is_already_map)
			tmp = tmp->next;
		else
		{
			line = ft_strtrim(tmp->line, "\n");
			if (ft_line_digit(line))
				is_already_map = 1;
			if (!new_file)	
				new_file = ft_file_new(line);
			else
				ft_file_add_back(&new_file, ft_file_new(line));
			free(line);
			tmp = tmp->next;
		}
	}
	ft_file_clear(&file);
	return (new_file);
}
/*----------------------------------------------------*/