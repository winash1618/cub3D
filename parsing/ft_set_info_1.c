/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:43:58 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 16:51:15 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_check_path_part(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (!ft_strcmp(ft_strrchr(str, '.'), ".xpm"))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_check_path(t_info *info, int *err)
{
	t_info	*tmp;

	tmp = info;
	if (*err)
		return ;
	while (tmp != NULL)
	{
		if (*err)
			break ;
		if (tmp->type == NO || tmp->type == SO
			|| tmp->type == WE
			|| tmp->type == EA)
			*err = ft_check_path_part(tmp->data);
		tmp = tmp->next;
	}
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	print_tab(char **nums)
{
	int	i;

	i = 0;
	while (nums[i])
	{
		printf("[%s]\n", nums[i]);
		i++;
	}
}
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
