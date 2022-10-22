/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:47:54 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 20:34:14 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_help1(t_data *img, t_loc *loc)
{
	loc->cameraX = 2 * loc->x / (double)(screenWidth) - 1;
	loc->rayDirX = img->dirX + img->planeX * loc->cameraX;
	loc->rayDirY = img->dirY + img->planeY * loc->cameraX;
	loc->mapX = (int)(img->posX);
	loc->mapY = (int)(img->posY);
	if (loc->rayDirX == 0)
		loc->deltaDistX = 1e30;
	else
		loc->deltaDistX = fabs(1 / loc->rayDirX);
	if (loc->rayDirY == 0)
		loc->deltaDistY = 1e30;
	else
		loc->deltaDistY = fabs(1 / loc->rayDirY);
}

void	raycast_help2(t_data *img, t_loc *loc)
{
	if (loc->rayDirX < 0)
	{
		loc->stepX = -1;
		loc->sideDistX = (img->posX - loc->mapX) * loc->deltaDistX;
	}
	else
	{
		loc->stepX = 1;
		loc->sideDistX = (loc->mapX + 1.0 - img->posX) * loc->deltaDistX;
	}
	if (loc->rayDirY < 0)
	{
		loc->stepY = -1;
		loc->sideDistY = (img->posY - loc->mapY) * loc->deltaDistY;
	}
	else
	{
		loc->stepY = 1;
		loc->sideDistY = (loc->mapY + 1.0 - img->posY) * loc->deltaDistY;
	}
}

void	raycast_help3(t_data *img, t_loc *loc)
{
	while (loc->hit == 0)
	{
		if (loc->sideDistX < loc->sideDistY)
		{
			loc->sideDistX += loc->deltaDistX;
			loc->mapX += loc->stepX;
			loc->side = 0;
		}
		else
		{
			loc->sideDistY += loc->deltaDistY;
			loc->mapY += loc->stepY;
			loc->side = 1;
		}
		if (ft_strlen(img->s[loc->mapX]) > loc->mapY)
			if (img->s[loc->mapX][loc->mapY] == '1')
				loc->hit = 1;
	}
}

void	raycast_help4(t_data *img, t_loc *loc)
{
	if (loc->side == 0)
		loc->perpWallDist = (loc->sideDistX - loc->deltaDistX);
	else
		loc->perpWallDist = (loc->sideDistY - loc->deltaDistY);
	loc->lineHeight = (int)(screenHeight / loc->perpWallDist);
	img->drawStart = -loc->lineHeight / 2 + screenHeight / 2;
		img->drawEnd = loc->lineHeight / 2 + screenHeight / 2;
	if (img->drawEnd >= screenHeight)
		img->drawEnd = screenHeight - 1;
	if (img->drawStart >= screenHeight)
		img->drawStart = 0;
	if (loc->side == 0)
		loc->wallX = img->posY + loc->perpWallDist * loc->rayDirY;
	else
		loc->wallX = img->posX + loc->perpWallDist * loc->rayDirX;
	loc->wallX -= floor((loc->wallX));
	loc->texX = (int)(loc->wallX * (double)(texWidth));
	if (loc->side == 0 && loc->rayDirX > 0)
		loc->texX = texWidth - loc->texX - 1;
	if (loc->side == 1 && loc->rayDirY < 0)
		loc->texX = texWidth - loc->texX - 1;
}
