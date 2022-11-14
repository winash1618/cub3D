/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:21:50 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 15:45:51 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief move up or down according to the keycode
 * 
 * @param keycode int value 0 for up, 2 for down
 * @param img data structure related to the graphical part of the game
 */
void	key_check_updown(int keycode, t_data *img)
{
	if (keycode == 2)
	{
		if (img->s[(int)(img->posx + img->planex * WALKSPEED)]
			[(int)(img->posy)] != '1')
			img->posx += img->planex * WALKSPEED;
		if (img->s[(int)(img->posx)]
			[(int)(img->posy + img->planey * WALKSPEED)] != '1')
			img->posy += img->planey * WALKSPEED;
	}
	if (keycode == 0)
	{
		if (img->s[(int)(img->posx - img->planex * WALKSPEED)]
			[(int)(img->posy)] != '1')
			img->posx -= img->planex * WALKSPEED;
		if (img->s[(int)(img->posx)]
			[(int)(img->posy - img->planey * WALKSPEED)] != '1')
			img->posy -= img->planey * WALKSPEED;
	}
}

/**
 * @brief move left or right according to the keycode
 * 
 * @param keycode int value 13 for right 1 for left
 * @param img data structure related to the game
 */
void	key_check_rightleft(int keycode, t_data *img)
{
	if (keycode == 13)
	{
		if (img->s[(int)(img->posx + img->dirx * WALKSPEED)]
			[(int)(img->posy)] != '1')
			img->posx += img->dirx * WALKSPEED;
		if (img->s[(int)(img->posx)]
			[(int)(img->posy + img->diry * WALKSPEED)] != '1')
			img->posy += img->diry * WALKSPEED;
	}
	if (keycode == 1)
	{
		if (img->s[(int)(img->posx - img->dirx * WALKSPEED)]
			[(int)(img->posy)] != '1')
			img->posx -= img->dirx * WALKSPEED;
		if (img->s[(int)(img->posx)]
			[(int)(img->posy - img->diry * WALKSPEED)] != '1')
			img->posy -= img->diry * WALKSPEED;
	}
}

/**
 * @brief rotate clock wise or anti clock wise according to the keycode
 * 
 * @param keycode if keycode is 123 rotate clockwise, else if 124 
 * rotate anti clock wise
 * @param img data structure related to graphical part the game
 */
void	key_check_rotate(int keycode, t_data *img)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 124)
	{
		old_dir_x = img->dirx;
		img->dirx = img->dirx * cos(-ROTSPEED) - img->diry * sin(-ROTSPEED);
		img->diry = old_dir_x * sin(-ROTSPEED) + img->diry * cos(-ROTSPEED);
		old_plane_x = img->planex;
		img->planex = img->planex * cos(-ROTSPEED)
			- img->planey * sin(-ROTSPEED);
		img->planey = old_plane_x * sin(-ROTSPEED)
			+ img->planey * cos(-ROTSPEED);
	}
	if (keycode == 123)
	{
		old_dir_x = img->dirx;
		img->dirx = img->dirx * cos(ROTSPEED) - img->diry * sin(ROTSPEED);
		img->diry = old_dir_x * sin(ROTSPEED) + img->diry * cos(ROTSPEED);
		old_plane_x = img->planex;
		img->planex = img->planex * cos(ROTSPEED) - img->planey * sin(ROTSPEED);
		img->planey = old_plane_x * sin(ROTSPEED) + img->planey * cos(ROTSPEED);
	}
}

/**
 * @brief here we execute three functions according to the keycode and change
 * the values of img->dirx, img->diry, plane->dirx and plane->diry after that
 * check if keycode is 53 true exit the program. after start the ray casting.
 * 
 * @param keycode int value corresponding to the key we pressed
 * @param img data structure related to graphical part of the game
 * @return int allways return 0
 */
int	key_check(int keycode, t_data *img)
{
	key_check_updown(keycode, img);
	key_check_rightleft(keycode, img);
	key_check_rotate(keycode, img);
	if (keycode == 53)
		ft_exit(img);
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, SCREENWIDTH, SCREENHEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	raycast(img);
	return (0);
}
