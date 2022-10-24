/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:47:54 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/24 09:51:19 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief here we start ray casting this one of the seven function used for
 * ray casting.
 * 
 * @param img data structure related image
 * @param loc data structure for raycasting only it contains all the local
 * variable need for raycasting.
 */
void	raycast_help1(t_data *img, t_loc *loc)
{
	loc->camerax = 2 * loc->x / (double)(SCREENWIDTH) - 1;
	loc->raydirx = img->dirx + img->planex * loc->camerax;
	loc->raydiry = img->diry + img->planey * loc->camerax;
	loc->mapx = (int)(img->posx);
	loc->mapy = (int)(img->posy);
	if (loc->raydirx == 0)
		loc->deltadistx = 1e30;
	else
		loc->deltadistx = fabs(1 / loc->raydirx);
	if (loc->raydiry == 0)
		loc->deltadisty = 1e30;
	else
		loc->deltadisty = fabs(1 / loc->raydiry);
}

/**
 * @brief here we get the value step in x direction and y direction
 * it is either positive one or negative one
 * setdistx distance to move in x direction(left or rigth) to reach x
 * side of the box
 * setdisty distance to move in y direction(left or rigth) to reach y
 * side of the box
 * 
 * @param img data structure related image
 * @param loc data structure for raycasting only it contains all the local
 * variable need for raycasting.
 */
void	raycast_help2(t_data *img, t_loc *loc)
{
	if (loc->raydirx < 0)
	{
		loc->stepx = -1;
		loc->sidedistx = (img->posx - loc->mapx) * loc->deltadistx;
	}
	else
	{
		loc->stepx = 1;
		loc->sidedistx = (loc->mapx + 1.0 - img->posx) * loc->deltadistx;
	}
	if (loc->raydiry < 0)
	{
		loc->stepy = -1;
		loc->sidedisty = (img->posy - loc->mapy) * loc->deltadisty;
	}
	else
	{
		loc->stepy = 1;
		loc->sidedisty = (loc->mapy + 1.0 - img->posy) * loc->deltadisty;
	}
}

/**
 * @brief DDA algorithm to find when we will hit the wall
 * 
 * @param img data structure related image
 * @param loc data structure for raycasting only it contains all the local
 * variable need for raycasting.
 */
void	raycast_help3(t_data *img, t_loc *loc)
{
	while (loc->hit == 0)
	{
		if (loc->sidedistx < loc->sidedisty)
		{
			loc->sidedistx += loc->deltadistx;
			loc->mapx += loc->stepx;
			loc->side = 0;
		}
		else
		{
			loc->sidedisty += loc->deltadisty;
			loc->mapy += loc->stepy;
			loc->side = 1;
		}
		if (ft_strlen(img->s[loc->mapx]) > loc->mapy)
			if (img->s[loc->mapx][loc->mapy] == '1')
				loc->hit = 1;
	}
}

/**
 * @brief find the perpendicular wall distance in terms of screenheight to
 * get the wall height along the screen width to get the 3D view. then save
 * where to start drawing the wall and where to end drawing the wall along the
 * screen height.
 * 
 * @param img data structure related graphical part of the game
 * @param loc data structure for raycasting only it contains all the local
 * variable need for raycasting.
 */
void	raycast_help4(t_data *img, t_loc *loc)
{
	if (loc->side == 0)
		loc->perpwalldist = (loc->sidedistx - loc->deltadistx);
	else
		loc->perpwalldist = (loc->sidedisty - loc->deltadisty);
	loc->lineheight = (int)(SCREENHEIGHT / loc->perpwalldist);
	img->drawstart = -loc->lineheight / 2 + SCREENHEIGHT / 2;
	img->drawend = loc->lineheight / 2 + SCREENHEIGHT / 2;
	if (img->drawend >= SCREENHEIGHT)
		img->drawend = SCREENHEIGHT - 1;
	if (img->drawstart >= SCREENHEIGHT)
		img->drawstart = 0;
	if (loc->side == 0)
		loc->wallx = img->posy + loc->perpwalldist * loc->raydiry;
	else
		loc->wallx = img->posx + loc->perpwalldist * loc->raydirx;
	loc->wallx -= floor((loc->wallx));
	loc->tex_x = (int)(loc->wallx * (double)(TEXWIDTH));
	if (loc->side == 0 && loc->raydirx > 0)
		loc->tex_x = TEXWIDTH - loc->tex_x - 1;
	if (loc->side == 1 && loc->raydiry < 0)
		loc->tex_x = TEXWIDTH - loc->tex_x - 1;
}
