/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:44:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 13:09:16 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	check_types_2(t_info *info)
{
	t_info	*tmp;
	t_info	*tmp2;
	int		count;

	tmp = info;
	tmp2 = info;
	while (tmp2)
	{
		tmp = info;
		count = 0;
		while (tmp)
		{
			if (tmp->type == tmp2->type)
				count++;
			tmp = tmp->next;
		}
		if (count > 1)
			return (0);
		tmp2 = tmp2->next;
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	check_types_1(t_info *info)
{
	t_info	*tmp;
	int		count;

	count = 0;
	tmp = info;
	while (tmp)
	{
		if (tmp->type == 6)
			return (0);
		count++;
		tmp = tmp->next;
	}
	if (count != 6 || !check_types_2(info)
		|| !check_types_3(info) || !ft_check_path(info))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	check_info(t_info *info)
{
	if (!check_types_1(info))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_info_part(t_info **info, char *str, int type)
{
	if (!*info)
		*info = ft_info_new(str, type);
	else
		ft_info_add_back(info, ft_info_new(str, type));
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
t_info	*ft_set_info(t_file *file, int *err)
{
	t_file	*tmp;
	t_info	*info;
	char	**tab;

	tmp = file;
	info = NULL;
	tab = NULL;
	while (tmp)
	{
		tab = ft_split(tmp->line, ' ');
		if (ft_tablen(tab) != 2)
		{
			*err = 1;
			ft_free_tab(tab);
			break ;
		}
		ft_info_part(&info, tab[1], ft_type(tab[0]));
		tmp = tmp->next;
		ft_free_tab(tab);
	}
	if (!check_info(info))
		*err = 1;
	ft_file_clear(&file);
	return (info);
}
/*----------------------------------------------------*/
