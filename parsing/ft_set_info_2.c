/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:08:15 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 13:38:26 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (ft_tablen(nums) != 3 || nb_comas(str) != 2)
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
	t_info	*tmp;

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
