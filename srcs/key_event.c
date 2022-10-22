/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:21:50 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 20:46:07 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_check_updown(int keycode, t_data *img)
{
	if (keycode == 2)
	{
		if (img->s[(int)(img->posX + img->planeX * walkspeed)]
			[(int)(img->posY)] != '1')
			img->posX += img->planeX * walkspeed;
		if (img->s[(int)(img->posX)]
			[(int)(img->posY + img->planeY * walkspeed)] != '1')
			img->posY += img->planeY * walkspeed;
	}
	if (keycode == 0)
	{
		if (img->s[(int)(img->posX - img->planeX * walkspeed)]
			[(int)(img->posY)] != '1')
			img->posX -= img->planeX * walkspeed;
		if (img->s[(int)(img->posX)]
			[(int)(img->posY - img->planeY * walkspeed)] != '1')
			img->posY -= img->planeY * walkspeed;
	}
}

void	key_check_rightleft(int keycode, t_data *img)
{
	if (keycode == 13)
	{
		if (img->s[(int)(img->posX + img->dirX * walkspeed)]
			[(int)(img->posY)] != '1')
			img->posX += img->dirX * walkspeed;
		if (img->s[(int)(img->posX)]
			[(int)(img->posY + img->dirY * walkspeed)] != '1')
			img->posY += img->dirY * walkspeed;
	}
	if (keycode == 1)
	{
		if (img->s[(int)(img->posX - img->dirX * walkspeed)]
			[(int)(img->posY)] != '1')
			img->posX -= img->dirX * walkspeed;
		if (img->s[(int)(img->posX)]
			[(int)(img->posY - img->dirY * walkspeed)] != '1')
			img->posY -= img->dirY * walkspeed;
	}
}

void	key_check_rotate(int keycode, t_data *img)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 123)
	{
		old_dir_x = img->dirX;
		img->dirX = img->dirX * cos(-rotspeed) - img->dirY * sin(-rotspeed);
		img->dirY = old_dir_x * sin(-rotspeed) + img->dirY * cos(-rotspeed);
		old_plane_x = img->planeX;
		img->planeX = img->planeX * cos(-rotspeed)
			- img->planeY * sin(-rotspeed);
		img->planeY = old_plane_x * sin(-rotspeed)
			+ img->planeY * cos(-rotspeed);
	}
	if (keycode == 124)
	{
		old_dir_x = img->dirX;
		img->dirX = img->dirX * cos(rotspeed) - img->dirY * sin(rotspeed);
		img->dirY = old_dir_x * sin(rotspeed) + img->dirY * cos(rotspeed);
		old_plane_x = img->planeX;
		img->planeX = img->planeX * cos(rotspeed) - img->planeY * sin(rotspeed);
		img->planeY = old_plane_x * sin(rotspeed) + img->planeY * cos(rotspeed);
	}
}

int	key_check(int keycode, t_data *img)
{
	key_check_updown(keycode, img);
	key_check_rightleft(keycode, img);
	key_check_rotate(keycode, img);
	if (keycode == 53)
		exit(1);
	raycast(img);
	return (0);
}
