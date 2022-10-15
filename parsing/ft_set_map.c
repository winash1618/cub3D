/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:40:04 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/15 15:31:34 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_is_valid_end(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_space_0(char *str, char *str1, char *str2, int i)
{
	if (str[i - 1] == ' ' || str[i + 1] == ' ')
		return (0);
	if (str1[i - 1] == ' ' || str1[i] == ' ' || str1[i + 1] == ' ')
		return (0);
	if (str2[i - 1] == ' ' || str2[i] == ' ' || str2[i + 1] == ' ')
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int ft_check_data2(char *str, char *str1, char *str2)
{
	if (str[0] == '0' || str1[0] == '0' || str2[0] == '0')
		return (0);
	if (str[ft_strlen(str) - 1] == '0' || str1[ft_strlen(str1) - 1] == '0' || str2[ft_strlen(str2) - 1] == '0')
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_data(t_map *line, t_map *line1, t_map *line2)
{
	int	i;

	i = 0;
	if (!line1)
		return (0);
	if (!line2)
	{
		if (!ft_is_valid_end(line->data))
			return (1);
	}
	if (line1 && line2)
	{
		if (!ft_check_data2(line->data, line1->data, line2->data))
			return (1);
		while (line->data[i])
		{
			if (line->data[i] == '0')
			{
				if (!ft_space_0(line->data, line1->data, line2->data, i))
					return (1);
			}
			i++;
		}
	}
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_map(t_map *map)
{
	t_map	*tmp;
	t_map	*line1;
	t_map	*line2;

	tmp = map;
	line1 = NULL;
	line2 = NULL;
	while (tmp != NULL)
	{
		if (tmp)
		{
			line1 = tmp->prev;
			line2 = tmp->next;
			if (ft_check_data(tmp, line1, line2))
				return (5);
		}
		tmp = tmp->next;
	}
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_handle_map(t_map **map, char *tmp)
{
	if (!*map)
		*map = ft_map_new(tmp);
	else
		ft_map_add_back(map, ft_map_new(tmp));
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	there_is_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_is_begmap(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] == ' ')
		i++;
	if (ft_isdigit(tmp[i]))
		return (1);
	return (0);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_start_point(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	// printf("str = %s\n", str);
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			count++;
		i++;
	}
	
	// printf("len = %d, i = %d\n", ft_strlen(str), i);
	return (count);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_is_linemap(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '1' || tmp[i] == '0' || tmp[i] == ' ' || tmp[i] == 'N'
			|| tmp[i] == 'S' || tmp[i] == 'E' || tmp[i] == 'W')
			i++;
		else
			return (0);
	}
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
t_map	*ft_set_map(int fd, int *err)
{
	(void)fd;
	(void)err;
	t_map	*map;
	char	*line;
	char	*tmp;
	int		is_already_map;
	int		end_map;
	int		start_point;

	tmp = NULL;
	map = NULL;
	line = NULL;
	is_already_map = 0;
	end_map = 0;
	start_point = 0;
	while(1)
	{
		line = get_next_line(fd);
		if (!line && end_map)
			*err = 4;
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, "\n", 1) || ft_spaces(line))
		{
			if (is_already_map)
				*err = 4;
			free(line);
			line = NULL;
			continue ;
		}
		if (there_is_new_line(line))
		{
			tmp = ft_strtrim(line, "\n");
			end_map = 1;
		}
		else
		{
			tmp = ft_strdup(line);
			end_map = 0;
		}
		if (ft_is_linemap(tmp))
		{
			is_already_map = 1;
			start_point += ft_start_point(tmp);
			ft_handle_map(&map, tmp);
			// printf("yeah->tmp = %s\n", tmp);
			free(tmp);
			tmp = NULL;
		}
		else if (is_already_map)
		{
			*err = 4;
			free(tmp);
			tmp = NULL;
		}
		else
		{
			free(tmp);
			tmp = NULL;
		}
		free(line);
		line = NULL;
	}
	*err = ft_check_map(map);
	ft_print_map(map);
	if (start_point != 1)
		*err = 3;
	return(map);
}
/*----------------------------------------------------*/
