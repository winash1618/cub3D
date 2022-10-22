/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:21:50 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:20:00 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_check_updown(int keycode, t_data *img)
{
	if (keycode == 2)
	{
		if (img->s[(int)(img->posX + img->planeX * WALKSPEED)]
			[(int)(img->posY)] != '1')
			img->posX += img->planeX * WALKSPEED;
		if (img->s[(int)(img->posX)]
			[(int)(img->posY + img->planeY * WALKSPEED)] != '1')
			img->posY += img->planeY * WALKSPEED;
	}
	if (keycode == 0)
	{
		if (img->s[(int)(img->posX - img->planeX * WALKSPEED)]
			[(int)(img->posY)] != '1')
			img->posX -= img->planeX * WALKSPEED;
		if (img->s[(int)(img->posX)]
			[(int)(img->posY - img->planeY * WALKSPEED)] != '1')
			img->posY -= img->planeY * WALKSPEED;
	}
}

void	key_check_rightleft(int keycode, t_data *img)
{
	if (keycode == 13)
	{
		if (img->s[(int)(img->posX + img->dirX * WALKSPEED)]
			[(int)(img->posY)] != '1')
			img->posX += img->dirX * WALKSPEED;
		if (img->s[(int)(img->posX)]
			[(int)(img->posY + img->dirY * WALKSPEED)] != '1')
			img->posY += img->dirY * WALKSPEED;
	}
	if (keycode == 1)
	{
		if (img->s[(int)(img->posX - img->dirX * WALKSPEED)]
			[(int)(img->posY)] != '1')
			img->posX -= img->dirX * WALKSPEED;
		if (img->s[(int)(img->posX)]
			[(int)(img->posY - img->dirY * WALKSPEED)] != '1')
			img->posY -= img->dirY * WALKSPEED;
	}
}

void	key_check_rotate(int keycode, t_data *img)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 123)
	{
		old_dir_x = img->dirX;
		img->dirX = img->dirX * cos(-ROTSPEED) - img->dirY * sin(-ROTSPEED);
		img->dirY = old_dir_x * sin(-ROTSPEED) + img->dirY * cos(-ROTSPEED);
		old_plane_x = img->planeX;
		img->planeX = img->planeX * cos(-ROTSPEED)
			- img->planeY * sin(-ROTSPEED);
		img->planeY = old_plane_x * sin(-ROTSPEED)
			+ img->planeY * cos(-ROTSPEED);
	}
	if (keycode == 124)
	{
		old_dir_x = img->dirX;
		img->dirX = img->dirX * cos(ROTSPEED) - img->dirY * sin(ROTSPEED);
		img->dirY = old_dir_x * sin(ROTSPEED) + img->dirY * cos(ROTSPEED);
		old_plane_x = img->planeX;
		img->planeX = img->planeX * cos(ROTSPEED) - img->planeY * sin(ROTSPEED);
		img->planeY = old_plane_x * sin(ROTSPEED) + img->planeY * cos(ROTSPEED);
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
