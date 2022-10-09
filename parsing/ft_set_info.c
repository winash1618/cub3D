/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:39:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/09 11:49:54 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	(void)err;
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
			*err = 1;
			ft_free_tab(nums);
			return ;
		}
		if (ft_strlen(nums[0]) > 3 || ft_strlen(nums[1]) > 3
			|| ft_strlen(nums[2]) > 3)
			*err = 1;
		if (ft_atoi(nums[0]) > 255 || ft_atoi(nums[1]) > 255
			|| ft_atoi(nums[2]) > 255)
			*err = 1;
	}
	ft_free_tab(nums);
}
/*----------------------------------------------------*/

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
		ft_valid_nums(tab[1], type, err);
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