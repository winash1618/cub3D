/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:11:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 13:55:20 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief convert the color from trgb to its respective integer standard
 * 
 * @param t transparency
 * @param r red
 * @param g green
 * @param b blue
 * @return int The color integer standard
 */
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * @brief Create color in integer standard from a given string
 * For example:
 * str = "120,255,3", each comma separated value is between 0-255
 * @param str string format of rgb saperated by comma
 * @return int The color integer standard
 */
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

/**
 * @brief print proper error message to stdout
 * 
 * @param err int value represent type of error
 */

/**
 * @brief check for any errors in parsing
 * 
 * @param parse data structure corresponding to the parsing
 * @param err pointer to the int represent type of error we 
 * may get by default it is zero
 * @return int return 0 in all cases
 */
int	check_parse(t_parse *parse, int *err)
{
	if (*err)
	{
		printf("Error: ...\n");
		ft_parse_clear(&parse);
		return (1);
	}
	return (0);
}

/**
 * @brief This is where we begin our program
 * 
 * @param ac number arguements given
 * @param av double string array representing arguements given
 * @return int return 0 in all case and exits the program
 */
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
	mlx_hook(img.win, 17, 1L << 17, ft_exit, &img);
	mlx_loop(img.mlx);
	return (0);
}
