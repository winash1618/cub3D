/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:39:34 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/03 22:19:16 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
t_file	*ft_clean_file(t_file *file)
{
	t_file	*tmp;
	t_file	*new_file;
	char	*line;

	new_file = NULL;
	tmp = file;
	while (tmp)
	{
		if (!ft_strcmp(tmp->line, "\n") || ft_spaces(tmp->line))
			tmp = tmp->next;
		else
		{
			line = ft_strtrim(tmp->line, "\n");
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