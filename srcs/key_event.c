/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:21:50 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/04 09:59:41 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void key_check_updown(int keycode, t_data *img)
// {
// 	if (keycode == 2)
// 	{
// 		if(img->s[(int)(img->posX + img->planeX * walkspeed)][(int)(img->posY)] != '1')
// 			img->posX += img->planeX * walkspeed;
// 		if(img->s[(int)(img->posX)][(int)(img->posY + img->planeY * walkspeed)] != '1')
// 			img->posY += img->planeY * walkspeed;
// 	}
// 	if (keycode == 0)
// 	{
// 		if(img->s[(int)(img->posX - img->planeX * walkspeed)][(int)(img->posY)] != '1')
// 			img->posX -= img->planeX * walkspeed;
// 		if(img->s[(int)(img->posX)][(int)(img->posY - img->planeY * walkspeed)] != '1')
// 			img->posY -= img->planeY * walkspeed;
// 	}
// }

// void key_check_rightleft(int keycode, t_data *img)
// {
// 	if (keycode == 13)
// 	{
// 		if(img->s[(int)(img->posX + img->dirX * walkspeed)][(int)(img->posY)] != '1')
// 			img->posX += img->dirX * walkspeed;
// 		if(img->s[(int)(img->posX)][(int)(img->posY + img->dirY * walkspeed)] != '1')
// 			img->posY += img->dirY * walkspeed;
// 	}
// 	if (keycode == 1)
// 	{
// 		if(img->s[(int)(img->posX - img->dirX * walkspeed)][(int)(img->posY)] != '1')
// 			img->posX -= img->dirX * walkspeed;
// 		if(img->s[(int)(img->posX)][(int)(img->posY - img->dirY * walkspeed)] != '1')
// 			img->posY -= img->dirY * walkspeed;
// 	}
// }

// void key_check_rotate(int keycode, t_data *img)
// {
// 	if (keycode == 123)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double oldDirX = img->dirX;
// 		img->dirX = img->dirX * cos(-rotspeed) - img->dirY * sin(-rotspeed);
// 		img->dirY = oldDirX * sin(-rotspeed) + img->dirY * cos(-rotspeed);
// 		double oldPlaneX = img->planeX;
// 		img->planeX = img->planeX * cos(-rotspeed) - img->planeY* sin(-rotspeed);
// 		img->planeY = oldPlaneX * sin(-rotspeed) + img->planeY * cos(-rotspeed);
// 		// printf("%f %f %f %f \n", img->dirX, img->dirY, img->planeX, img->planeY);
// 	}
// 	if (keycode == 124)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double oldDirX = img->dirX;
// 		img->dirX = img->dirX*cos(rotspeed) - img->dirY*sin(rotspeed);
// 		img->dirY = oldDirX *sin(rotspeed)+ img->dirY*cos(rotspeed);
// 		double oldPlaneX = img->planeX;
// 		img->planeX = img->planeX *cos(rotspeed)- img->planeY*sin(rotspeed);
// 		img->planeY = oldPlaneX*sin(rotspeed) + img->planeY*cos(rotspeed);
// 		// printf("%f %f %f %f \n", img->dirX, img->dirY, img->planeX, img->planeY);
// 	}
// }

// int	key_check(int keycode, t_data *img)
// {
// 	key_check_updown(keycode, img);
// 	key_check_rightleft(keycode, img);
// 	key_check_rotate(keycode, img);
// 	if (keycode == 53)
// 		exit(1);
// 	raycast(img);
// 	return (0);
// }