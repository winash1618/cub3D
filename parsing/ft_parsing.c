/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:17:14 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 12:44:29 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*----------------------------------------------------*/
int	ft_parsing_part(t_file *file, t_parse **parse, int *err)
{
	t_file	*help_file;

	help_file = ft_save_info(file);
	(*parse)->info = ft_set_info(help_file, err);
	if (*err || !(*parse)->info)
	{
		ft_file_clear(&file);
		return (0);
	}
	help_file = ft_save_map(file);
	if (!help_file || !ft_valid_map(help_file))
	{
		ft_file_clear(&help_file);
		ft_file_clear(&file);
		return (0);
	}
	(*parse)->map = ft_set_map(help_file);
	ft_file_clear(&file);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_parser(char *av, t_parse **parse)
{
	int		err;
	t_file	*file;

	err = 0;
	file = ft_making_file(av, &err);
	if (err || !file)
	{
		ft_file_clear(&file);
		return (0);
	}
	if (!ft_parsing_part(file, parse, &err))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
void	ft_parse_clear(t_parse **parse)
{
	if (!parse || !*parse)
		return ;
	if ((*parse)->map)
		ft_map_clear(&(*parse)->map);
	if ((*parse)->info)
		ft_info_clear(&(*parse)->info);
	free(*parse);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_check_av(char *str)
{
	if (!ft_strcmp(ft_strrchr(str, '.'), ".cub"))
		return (0);
	return (1);
}
/*----------------------------------------------------*/

/*----------------------------------------------------*/
int	ft_parsing(int ac, char **av, t_parse **parse)
{
	if ((ac == 1) || (ac > 2) || ft_check_av(av[1]))
		return (1);
	*parse = (t_parse *)malloc(sizeof(t_parse));
	(*parse)->info = NULL;
	(*parse)->map = NULL;
	if (!ft_parser(av[1], parse))
		return (1);
	ft_print_info((*parse)->info);
	ft_print_map((*parse)->map);
	return (0);
}
/*----------------------------------------------------*/