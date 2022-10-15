/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:10:36 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/04 09:59:33 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	ft_exit(void)
// {
// 	exit (1);
// 	return (0);
// }

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// void check_name(char *str)
// {
// 	while(*str)
// 	{
// 		if(*str == '.')
// 		{
// 			if (strcmp(str + 1, "cub"))
// 			{
// 				exit(EXIT_FAILURE);
// 			}
// 			else
// 				break;
// 		}
// 		str++;
// 	}
// }

// char **create_map(int ac, char **av)
// {
// 	int fd;
// 	// int line_num;
// 	fd = 0;
// 	char *str;
// 	int count = 0;
// 	char **s;
// 	s = NULL;
// 	str = NULL;
// 	int i;
// 	if (ac == 2)
// 	{
// 		fd = open(ft_strjoin("./map/", av[1], 0), O_RDONLY);
// 		check_name(av[1]);
// 		str = get_next_line(fd);
// 		count++;
// 		if (!str)
// 			return (0);
// 		else
// 		{
// 			while (str)
// 			{
// 				str = get_next_line(fd);
// 				count++;
// 			}
// 		}
// 		close (fd);
// 		fd = open(ft_strjoin("./map/", av[1], 0), O_RDONLY);
// 		s = (char **)malloc(sizeof(char *) * (count));
// 		i = 0;
// 		while (i < count)
// 		{
// 			s[i] = ft_strtrim(get_next_line(fd), "\n");
// 			i++;
// 		}
// 	}
// 	close(fd);
// 	i = 0;
// 	return (s);
// }

