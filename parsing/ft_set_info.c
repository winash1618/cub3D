/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:44:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/09 19:15:51 by mkaruvan         ###   ########.fr       */
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

/*----------------------------------------------------*/

/*----------------------------------------------------*/
/*----------------------------------------------------*/
int	ft_only_nums(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == ',')
			i++;
		else
			return (0);
	}
	return (1);
}
/*----------------------------------------------------*/

int	ft_valid_nums(char *str, int type)
{
	char	**nums;
	int		ret;

	ret = 1;
	nums = NULL;
	if (!str)
		return (0);
	if (type == F || type == C)
	{
		if (!ft_only_nums(str))
			ret = 0;
		nums = ft_split(str, ',');
		if (ft_tablen(nums) != 3)
			ret = 0;
		if (ft_atoi(nums[0]) > 255 || ft_atoi(nums[1]) > 255
			|| ft_atoi(nums[2]) > 255)
			ret = 0;
		if (ft_atoi(nums[0]) < 0 || ft_atoi(nums[1]) < 0
			|| ft_atoi(nums[2]) < 0)
			ret = 0;
	}
	else
		return (1);
	ft_free_tab(nums);
	return (ret);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_path_part(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	if (!ft_strcmp(ft_strrchr(str, '.'), ".xpm"))
		return (1);
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_path(t_info *info)
{
	t_info	*tmp;
	int		ret;

	ret = 1;
	tmp = info;
	while (tmp)
	{
		if (!ret)
			break ;
		if (tmp->type == NO || tmp->type == SO
			|| tmp->type == WE
			|| tmp->type == EA)
			ret = ft_check_path_part(tmp->data);
		tmp = tmp->next;
	}
	return (ret);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	check_types_3(t_info *info)
{
	t_info *tmp;

	tmp = info;
	while (tmp)
	{
		if (!ft_valid_nums(tmp->data, tmp->type))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
/*----------------------------------------------------*/

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
	int count;

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
		if (!info)
			info = ft_info_new(tab[1], ft_type(tab[0]));
		else
			ft_info_add_back(&info, ft_info_new(tab[1], ft_type(tab[0])));
		tmp = tmp->next;
		ft_free_tab(tab);
	}
	if (!check_info(info))
		*err = 1;
	ft_file_clear(&file);
	return (info);
}
/*----------------------------------------------------*/
