/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:51:54 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 13:54:55 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_valid_line(char *line, int i, int *err)
{
	while (line[i])
	{
		if (line[i] == '1'
			|| line[i] == ' '
			|| line[i] == '\n')
			i++;
		else
		{
			*err = 1;
			return (0);
		}
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_is_map(char *line, int *err)
{
	int	i;

	i = 0;
	while ((line)[i])
	{
		while (((line))[i] == ' ')
			i++;
		if ((line)[i] == '1'
			|| (line)[i] == '0'
			|| (line)[i] == ' ')
		{
			if (!ft_valid_line(line, i, err))
			{
				*err = 1;
				return (1);
			}
			return (1);
		}
		else
		{
			return (0);
		}
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_type(char *str)
{
	char	*tmp;
	int		ret;

	tmp = ft_rm_spaces(str);
	if (ft_strncmp(tmp, "NO ", 3) == 0)
		ret = 0;
	else if (ft_strncmp(tmp, "SO ", 3) == 0)
		ret = 1;
	else if (ft_strncmp(tmp, "WE ", 3) == 0)
		ret = 2;
	else if (ft_strncmp(tmp, "EA ", 3) == 0)
		ret = 3;
	else if (ft_strncmp(tmp, "F ", 2) == 0)
		ret = 4;
	else if (ft_strncmp(tmp, "C ", 2) == 0)
		ret = 5;
	else
		ret = 6;
	free(tmp);
	return (ret);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_info(char *line)
{
	char	*str;

	str = line;
	while (*str == ' ')
		str++;
	if (ft_strncmp(str, "NO ", 3) == 0
		|| ft_strncmp(str, "SO ", 3) == 0
		|| ft_strncmp(str, "WE ", 3) == 0
		|| ft_strncmp(str, "EA ", 3) == 0
		|| ft_strncmp(str, "F ", 2) == 0
		|| ft_strncmp(str, "C ", 2) == 0)
		return (1);
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_handle_info(char *line, t_info **info, int *err)
{
	char	*str;
	char	**tab;
	int		type;

	str = NULL;
	tab = NULL;
	if (ft_check_info(line))
	{
		str = ft_strtrim(line, "\n");
		type = ft_type(str);
		tab = ft_split(str, ' ');
		free(str);
		if (ft_tablen(tab) != 2)
			*err = 1;
		ft_valid_nums(tab[1], type, err);
		if (!(*info))
			(*info) = ft_info_new(tab[1], type);
		else
			ft_info_add_back(info, ft_info_new(tab[1], type));
		ft_free_tab(tab);
	}
	else
		*err = 1;
}
/*----------------------------------------------------*/
