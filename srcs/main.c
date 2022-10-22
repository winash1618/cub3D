/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:11:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:16:54 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	create_color(char *str)
{
	char	**s;
	int		a[3];
	int		i;

	s = ft_split(str, ',');
	i = 0;
	while (s[i])
	{
		a[i] = ft_atoi(s[i]);
		free(s[i]);
		i++;
	}
	free (s);
	return (create_trgb(0, a[0], a[1], a[2]));
}

void	ft_error(int err)
{
	if (err == 1)
		printf("Error: Invalid file.\n");
	else if (err == 2)
		printf("Error: Invalid file format.\n");
	else if (err == 3)
		printf("Error: Invalid Configuration Map.\n");
	else if (err == 4)
		printf("Error: Invalid line in the Map.\n");
	else if (err == 5)
		printf("Error: Invalid Map.\n");
	else if (err == 6)
		printf("Error: Invalid File Name.\n");
	else if (err == 7)
		printf("Error: Invalid Arguments.\n");
	else
		printf("Error: ...\n");
}

int	check_parse(t_parse *parse, int *err)
{
	if (parse)
		ft_check_path(parse->info, err);
	if (*err)
	{
		ft_error(*err);
		ft_parse_clear(&parse);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		err;
	t_parse	*parse;
	t_data	img;

	err = 0;
	parse = NULL;
	err = ft_parsing(ac, av, &parse);
	if (check_parse(parse, &err))
		return (0);
	ft_map_organize(&img, parse);
	ft_init_player(&img);
	ft_put_player(&img);
	img.mlx = mlx_init();
	if (!img.mlx)
		exit(0);
	img.win = mlx_new_window(img.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3D");
	img.img = mlx_new_image(img.mlx, SCREENWIDTH, SCREENHEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	image_putter(&img);
	raycast(&img);
	mlx_hook(img.win, 2, 0, key_check, &img);
	mlx_hook(img.win, 17, 1L << 17, ft_exit, 0);
	mlx_loop(img.mlx);
	return (0);
}
