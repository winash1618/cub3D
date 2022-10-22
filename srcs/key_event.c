/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:21:50 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:29:32 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	key_check_rotate(int keycode, t_data *img)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 123)
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
	if (keycode == 124)
	{
		old_dir_x = img->dirx;
		img->dirx = img->dirx * cos(ROTSPEED) - img->diry * sin(ROTSPEED);
		img->diry = old_dir_x * sin(ROTSPEED) + img->diry * cos(ROTSPEED);
		old_plane_x = img->planex;
		img->planex = img->planex * cos(ROTSPEED) - img->planey * sin(ROTSPEED);
		img->planey = old_plane_x * sin(ROTSPEED) + img->planey * cos(ROTSPEED);
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
