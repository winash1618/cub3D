/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:02:47 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 13:04:00 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_type(char *str)
{
	int	ret;

	if (ft_strcmp(str, "NO") == 0)
		ret = 0;
	else if (ft_strcmp(str, "SO") == 0)
		ret = 1;
	else if (ft_strcmp(str, "WE") == 0)
		ret = 2;
	else if (ft_strcmp(str, "EA") == 0)
		ret = 3;
	else if (ft_strcmp(str, "F") == 0)
		ret = 4;
	else if (ft_strcmp(str, "C") == 0)
		ret = 5;
	else
		ret = 6;
	return (ret);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
/*----------------------------------------------------*/

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