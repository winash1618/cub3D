/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:39:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/08 16:20:40 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_spaces(char *line)
{
	char *str;

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
	// (void)err;

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
				printf("checking valid map\n");
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
	char *str;

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
	if(ft_check_info(line))
	{
		str = ft_strtrim(line, "\n");
		type = ft_type(str);
		tab = ft_split(str, ' ');
		free(str);
		if (ft_tablen(tab) != 2)
			*err = 1;
		if(!(*info))
			(*info) = ft_info_new(tab[1], type);
		else
			ft_info_add_back(info, ft_info_new(tab[1], type));
		ft_free_tab(tab);
	}
	else
		*err = 1;
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
t_info	*ft_set_info(int fd, int *err)
{
	t_info	*info;
	char	*line;
	(void)err;

	info = NULL;
	line = NULL;
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, "\n", 1) || ft_spaces(line))
		{
			free(line);
			// line = NULL;
			continue ;
		}
		// printf("spacess: %d\n", ft_spaces(line));
		if (ft_is_map(line, err))
		{
			
			free(line);
			// line = NULL;
			break ;
		}
		ft_handle_info(line, &info, err);
		free(line);
		// line = NULL;
	}
	ft_print_info(info);
	return(info);
}
/*----------------------------------------------------*/