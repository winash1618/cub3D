/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:40:04 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/12 09:03:09 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	char	*line;
	char	*tmp;
	t_map	*map;
	int		count;
	int		alreadymap;

	map = NULL;
	count = 0;
	alreadymap = 0;
	line = NULL;
	tmp = NULL;
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, "\n", 1) || ft_spaces(line))
		{
			free(line);
			line = NULL;
			if (alreadymap)
				*err = 4;
			continue ;
		}
		tmp = ft_strtrim(line, "\n");
		if (ft_is_linemap(tmp))
		{
			alreadymap = 1;
			printf("tmp: [%s]----{%d}\n", tmp, ft_is_linemap(tmp));
			free(line);
			free(tmp);
			// printf("tmp: [%s]----{%d}\n", tmp, ft_is_linemap(tmp));
			// ft_is_validlinemap(tmp, err);
			count += ft_start_point(tmp);
		}
		// else if ()
		free(tmp);
		free(line);
		// line = NULL;
	}
	if (count != 1)
		*err = 3;
	return(map);
}
/*----------------------------------------------------*/
// /*----------------------------------------------------*/
// t_map	*ft_set_map(int fd, int *err)
// {
// 	(void)fd;
// 	(void)err;
// 	char	*line;
// 	char	*tmp;
// 	t_map	*map;
// 	int		count;
// 	int		alreadymap;

// 	map = NULL;
// 	count = 0;
// 	alreadymap = 0;
// 	while(1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break ;
// 		if (!ft_strncmp(line, "\n", 1) || ft_spaces(line))
// 		{
// 			free(line);
// 			line = NULL;
// 			if (alreadymap)
// 				*err = 4;
// 			continue ;
// 		}
// 		tmp = ft_strtrim(line, "\n");
// 		if (ft_is_linemap(tmp))
// 		{
// 			printf("tmp: [%s]----{%d}\n", tmp, ft_is_linemap(tmp));
// 			free(line);
// 			free(tmp);
// 			while(1)
// 			{
// 				line = get_next_line(fd);
// 				if (line == NULL)
// 					break ;
// 				if (!ft_strncmp(line, "\n", 1) || ft_spaces(line))
// 				{
// 					free(line);
// 					line = NULL;
// 					// if (alreadymap)
// 						*err = 4;
// 				}
// 				else {	
// 					tmp = ft_strtrim(line, "\n");
// 					if (ft_is_linemap(tmp))
// 					{
// 						// printf("tmp: [%s]----{%d}\n", tmp, ft_is_linemap(tmp));
// 						// ft_is_validlinemap(tmp, err);
// 						count += ft_start_point(tmp);
// 					}
// 					else
// 					{
// 						// printf("tmp: [%s]----{%d}\n", tmp, ft_is_linemap(tmp));
// 						*err = 4;
// 						// alreadymap = 1;
// 					}
// 					free(tmp);
// 					free(line);
// 					line = NULL;
// 				}
// 			}
// 			// free(tmp);
// 			// free(line);
// 			// printf("tmp: [%s]----{%d}\n", tmp, ft_is_linemap(tmp));
// 			// ft_is_validlinemap(tmp, err);
// 			// count += ft_start_point(tmp);
// 			continue;
// 		}
// 		free(tmp);
// 		free(line);
// 		// line = NULL;
// 	}
// 	if (count != 1)
// 		*err = 3;
// 	return(map);
// }
// /*----------------------------------------------------*/