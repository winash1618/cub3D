/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:47:54 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:31:17 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_help1(t_data *img, t_loc *loc)
{
	loc->cameraX = 2 * loc->x / (double)(SCREENWIDTH) - 1;
	loc->raydirx = img->dirx + img->planex * loc->cameraX;
	loc->raydiry = img->diry + img->planey * loc->cameraX;
	loc->mapX = (int)(img->posx);
	loc->mapY = (int)(img->posy);
	if (loc->raydirx == 0)
		loc->deltaDistX = 1e30;
	else
		loc->deltaDistX = fabs(1 / loc->raydirx);
	if (loc->raydiry == 0)
		loc->deltaDistY = 1e30;
	else
		loc->deltaDistY = fabs(1 / loc->raydiry);
}

void	raycast_help2(t_data *img, t_loc *loc)
{
	if (loc->raydirx < 0)
	{
		loc->stepX = -1;
		loc->sideDistX = (img->posx - loc->mapX) * loc->deltaDistX;
	}
	else
	{
		loc->stepX = 1;
		loc->sideDistX = (loc->mapX + 1.0 - img->posx) * loc->deltaDistX;
	}
	if (loc->raydiry < 0)
	{
		loc->stepY = -1;
		loc->sideDistY = (img->posy - loc->mapY) * loc->deltaDistY;
	}
	else
	{
		loc->stepY = 1;
		loc->sideDistY = (loc->mapY + 1.0 - img->posy) * loc->deltaDistY;
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
	loc->lineHeight = (int)(SCREENHEIGHT / loc->perpWallDist);
	img->drawstart = -loc->lineHeight / 2 + SCREENHEIGHT / 2;
		img->drawend = loc->lineHeight / 2 + SCREENHEIGHT / 2;
	if (img->drawend >= SCREENHEIGHT)
		img->drawend = SCREENHEIGHT - 1;
	if (img->drawstart >= SCREENHEIGHT)
		img->drawstart = 0;
	if (loc->side == 0)
		loc->wallX = img->posy + loc->perpWallDist * loc->raydiry;
	else
		loc->wallX = img->posx + loc->perpWallDist * loc->raydirx;
	loc->wallX -= floor((loc->wallX));
	loc->texX = (int)(loc->wallX * (double)(TEXWIDTH));
	if (loc->side == 0 && loc->raydirx > 0)
		loc->texX = TEXWIDTH - loc->texX - 1;
	if (loc->side == 1 && loc->raydiry < 0)
		loc->texX = TEXWIDTH - loc->texX - 1;
}
