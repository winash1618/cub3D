/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:39:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/08 10:57:23 by mkaruvan         ###   ########.fr       */
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
			printf("char: [%c], {%d}\n", line[i], i);
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
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '1'
			|| line[i] == '0'
			|| line[i] == ' ')
		{
			if (!ft_valid_line(line, i, err))
				break ;
			return (1);
		}
		else
			return (0);
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_type(char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		return (0);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		return (2);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		return (3);
	else if (ft_strncmp(str, "F ", 2) == 0)
		return (4);
	else if (ft_strncmp(str, "C ", 2) == 0)
		return (5);
	else
		return (6);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int ft_check_info(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_handle_info(char *line, t_info **info, int *err)
{
	(void)line;
	(void)info;
	(void)err;
	char	*str;
	// char	**tab;

	// printf("line: [%s]\n", line);
	if(ft_check_info(line))
	{
		str = ft_strtrim(line, "\n");
		// printf("str: [%s]\n", str); // TODO: remove
		if(!(*info))
			(*info) = ft_info_new(str, ft_type(str));
		else
			ft_info_add_back(info, ft_info_new(str, ft_type(str)));
	}
	else
		*err = 1;
	// printf("(*info): [%s]\n", (*info)->data);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
t_info	*ft_set_info(int fd, int *err)
{
	t_info	*info;
	char	*line;

	info = NULL;
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, "\n", 1))
			continue ;
		if (ft_is_map(line, err))
		{
			free(line);
			break ;
		}
		// printf("=> %s\n", line);
		ft_handle_info(line, &info, err);
		free(line);
	}
	// printf("info: [%s]\n", info->data);
	// printf("line: [%s]\n", line);
	ft_print_info(info);
	return(info);
}
/*----------------------------------------------------*/