/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:20:42 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/08 17:50:18 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/*----------------------------------------------------*/
int	start_pos(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			count++;
		i++;
	}
	return (count);
}
/*----------------------------------------------------*/

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

/*----------------------------------------------------*/
int	empty_space(char *str)
{
	if (ft_strlen(str) == 0)
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	all_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
			return (1);
	}
	if (!line[i])
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	start_end_well(char *line)
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
	if (line[i] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	valid_line_map(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if ((line[i] != ' ') && (line[i] != '1') && (line[i] != '0')
			&& (line[i] != 'E') && (line[i] != 'N') && (line[i] != 'S')
			&& ( line[i] != 'W'))
			return (0);
		i++;
	}
	if (!empty_space(line) || !all_spaces(line) || !start_end_well(line))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	check_first_last(t_file *file)
{
	t_file *tmp;
	t_file *tmp2;
	int	i;

	i = 0;
	tmp = file;
	tmp2 = file;
	while(tmp->line[i])
	{
		if (tmp->line[i] != '1' && tmp->line[i] != ' ')
			return (0);
		i++;
	}
	while(tmp2 && tmp2->next)
		tmp2 = tmp2->next;
	i = 0;
	while(tmp2->line[i])
	{
		if (tmp2->line[i] != '1' && tmp2->line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_space_0(char *str, int i)
{
	if (str[i] && (str[i] == ' ' || str[i - 1] == ' ' || str[i + 1] == ' '))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_space_0_part(char *str, int i)
{
	if (ft_strlen(str) >= i)
		return (0);
	if (str[i] && (str[i] == ' ' || str[i - 1] == ' ' || str[i + 1] == ' '))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	check_zero(t_file *file)
{
	t_file *tmp;
	int	i;

	tmp = file;
	i = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] == '0')
			{
				if (tmp && !ft_space_0(tmp->line, i))
					return (0);
				if (tmp && tmp->next && !ft_space_0_part(tmp->next->line, i))
					return (0);
				if (tmp && tmp->prev && !ft_space_0_part(tmp->prev->line, i))
					return (0);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_valid_map(t_file *file)
{
	t_file	*tmp;
	int		pos;

	tmp = file;
	pos = 0;
	while (tmp)
	{
		if (!valid_line_map(tmp->line))
			return (0);
		pos += start_pos(tmp->line);
		tmp = tmp->next;
	}
	if (!check_first_last(file) || !check_zero(file) || pos != 1)
		return (0);
	return (1);
}
/*----------------------------------------------------*/
