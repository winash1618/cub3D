/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_play.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:39:05 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 15:43:32 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief first it will convert xpm file to image then position that image on to
 * the window
 * 
 * @param img data structure related to the image. 
 */
void	image_putter(t_data *img)
{
	img->ptr[NO] = mlx_xpm_file_to_image(img->mlx, img->i[NO],
			&img->width[NO], &img->height[NO]);
	img->texture[NO] = (int (*))mlx_get_data_addr(img->ptr[NO],
			&img->bpp[NO], &img->ll[NO], &img->en[NO]);
	img->ptr[SO] = mlx_xpm_file_to_image(img->mlx, img->i[SO],
			&img->width[SO], &img->height[SO]);
	img->texture[SO] = (int (*))mlx_get_data_addr(img->ptr[SO],
			&img->bpp[SO], &img->ll[SO], &img->en[SO]);
	img->ptr[WE] = mlx_xpm_file_to_image(img->mlx, img->i[WE],
			&img->width[WE], &img->height[WE]);
	img->texture[WE] = (int (*))mlx_get_data_addr(img->ptr[WE],
			&img->bpp[WE], &img->ll[WE], &img->en[WE]);
	img->ptr[EA] = mlx_xpm_file_to_image(img->mlx, img->i[EA],
			&img->width[EA], &img->height[EA]);
	img->texture[EA] = (int (*))mlx_get_data_addr(img->ptr[EA], &img->bpp[EA],
			&img->ll[EA], &img->en[EA]);
}

/**
 * @brief set direction of the player according the character
 * representing the player N - north, E - East, S - South, W - West
 * 
 * @param img data structure related to the image
 * @param j int value corresponding map x co ordinate
 * @param k int value corresponding map y co ordinate
 */
void	ft_set_player_dir(t_data *img, int j, int k)
{
	if (img->s[j][k] == 'N')
	{
		img->dirx = 1;
		img->planey = -0.66;
	}
	else if (img->s[j][k] == 'W')
	{
		img->diry = 1;
		img->planex = 0.66;
	}
	else if (img->s[j][k] == 'E')
	{
		img->diry = -1;
		img->planex = -0.66;
	}
	else
	{
		img->dirx = -1;
		img->planey = 0.66;
	}
}

/**
 * @brief position the player in the map according to where player
 * is located in the double string array player can N, E, S, W
 * 
 * @param img data structure related to the image
 */
void	ft_put_player(t_data *img)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (img->s[j])
	{
		k = 0;
		while (img->s[j][k])
		{
			if (img->s[j][k] == 'W' || img->s[j][k] == 'N'
				|| img->s[j][k] == 'S' || img->s[j][k] == 'E')
			{
				img->posx = j + 0.5;
				img->posy = k + 0.5;
				ft_set_player_dir(img, j, k);
				break ;
			}
			k++;
		}
		j++;
	}
}

/**
 * @brief initializing position, direction and plane
 * the player is currently present.
 * 
 * @param img data structure related to image.
 */
void	ft_init_player(t_data *img)
{
	img->posx = 0;
	img->posy = 0;
	img->dirx = 0;
	img->diry = 0;
	img->planex = 0;
	img->planey = 0;
	img->drawstart = 0;
	img->drawend = 0;
}

/**
 * @brief Organise the map after parsing, here we are doing four
 * things first we convert data structure after parsing that contains
 * two linked list related to info and map into double string
 * array then we save map info in double array in to img->i and map data
 * in double array in to img->s. after that we get the floor color
 * from img->i[F] which contain floor color in string (r,g,b) format store
 * it in img->floor_color which is an integer value, then same is done for
 * ceiling color. Now free p that was malloced in create map.
 * 
 * @param img data structure related to graphical part of the game
 * @param parse data structure related to parsing
 */
void	ft_map_organize(t_data *img, t_parse *parse)
{
	char	***p;

	p = create_map(parse);
	ft_parse_clear(&parse);
	img->i = p[0];
	img->s = p[1];
	img->floor_color = create_color(img->i[F]);
	img->ceiling_color = create_color(img->i[C]);
	free(p);
}
