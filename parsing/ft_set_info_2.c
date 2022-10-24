/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:48:12 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 19:56:28 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
char	*ft_rm_spaces(char *str)
{
	int		i;
	int		len;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	len = ft_strlen(str) - i;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[j] = str[i];
		i++;
		j++;
	}
	return (new);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_valid_nums(char *str, int type, int *err)
{
	char	**nums;

	nums = NULL;
	if (type == F || type == C)
	{
		if (!ft_only_nums(str))
		{
			*err = 1;
			return ;
		}
		nums = ft_split(str, ',');
		if (ft_tablen(nums) != 3)
		{
			*err = 8;
			ft_free_tab(nums);
			return ;
		}
		if (ft_strlen(nums[0]) > 3 || ft_strlen(nums[1]) > 3
			|| ft_strlen(nums[2]) > 3)
			*err = 1;
		if (ft_atoi(nums[0]) > 255 || ft_atoi(nums[1]) > 255
			|| ft_atoi(nums[2]) > 255)
			*err = 8;
	}
	ft_free_tab(nums);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_spaces(char *line)
{
	char	*str;

	str = line;
	while (*str == ' ')
		str++;
	if (!str || !ft_strcmp(str, "\n"))
		return (1);
	return (0);
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
