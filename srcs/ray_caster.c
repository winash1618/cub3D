/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:11:48 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/25 07:05:10 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This funciton adds pixels along the screenheight using my_mlx_pixel_put
 * we have the location of the pixel on the screen and the color of the pixel
 * 
 * @param img data structure related graphical part of the game
 * @param loc data structure for raycasting only it contains all the local
 * variable need for raycasting.
 */
void	raycast_help6(t_data *img, t_loc *loc)
{
	unsigned int	i;

	i = 0;
	while (i < SCREENHEIGHT)
	{
		if (i < SCREENHEIGHT / 2)
			my_mlx_pixel_put(img, loc->x, i, img->floor_color);
		else if (i > SCREENHEIGHT / 2)
			my_mlx_pixel_put(img, loc->x, i, img->ceiling_color);
		i++;
	}
	i = 0;
	while (i < SCREENHEIGHT)
	{
		if (i >= img->drawstart && i <= img->drawend)
		{
			my_mlx_pixel_put(img, loc->x, i, img->buffer[i][loc->x]);
		}
		i++;
	}
}

void	raycast_help7(t_data *img, t_loc *loc)
{
	loc->step = 1.0 * TEXHEIGHT / loc->lineheight;
	loc->texpos = (img->drawstart - SCREENHEIGHT / 2
			+ loc->lineheight / 2) * loc->step;
	loc->y = 0;
}

/**
 * @brief first we will go to the ray cast help 7 which made just to
 * satisfy the norminette. It will set step
 * then calculate texture position in the image according to the 
 * number of steps, set y = 0. then we will while loop until y < screen height
 * if y is between draw start and draw end we get the corresponding color
 * from the texture accoding to which type of wall it is, remember we have
 * four walls. then we darken the color of wall whoose side is one to get
 * that 3d effect and then store the color value in buffer.
 * 
 * @param img data structure related graphical part of the game
 * @param loc data structure for raycasting only it contains all the local
 * variable need for raycasting.
 */
void	raycast_help5(t_data *img, t_loc *loc)
{
	raycast_help7(img, loc);
	while (loc->y < SCREENHEIGHT)
	{
		if (loc->y >= img->drawstart && loc->y <= img->drawend)
		{
			loc->tex_y = (int)loc->texpos & (img->height[0] - 1);
			loc->texpos += loc->step;
			if (loc->side == 0 && loc->raydirx > 0)
				loc->color = (int)img->texture[0][(int)
					TEXHEIGHT * loc->tex_y + loc->tex_x];
			else if (loc->side == 0 && loc->raydirx < 0)
				loc->color = (int)img->texture[1][(int)
					TEXHEIGHT * loc->tex_y + loc->tex_x];
			else if (loc->side == 1 && loc->raydiry > 0)
				loc->color = (int)img->texture[2][(int)
					TEXHEIGHT * loc->tex_y + loc->tex_x];
			else if (loc->side == 1 && loc->raydiry < 0)
				loc->color = (int)img->texture[3][(int)
					TEXHEIGHT * loc->tex_y + loc->tex_x];
			if (loc->side == 1)
				loc->color = (loc->color >> 1) & 8355711;
			img->buffer[loc->y][loc->x] = loc->color;
		}
		loc->y++;
	}
}

/**
 * @brief this is an helper funtion for raycasting
 * init local is for initializing the local variable of raycasting
 * raycast_help1 is for intializing some variable to the required value
 * raycast_help2 is for step in x direction and y direction
 * raycast_help3 is for DDA algorithm
 * raycast_help4 is for finding wall height and where it starts and end
 * raycast_help5 is for find the color of each pixel in the screen
 * raycast_help6 is for storing pixel data in to memory so that later
 * we can display it.
 * 
 * @param img data structure related to the graphical part of the game.
 * @param x int value corresponding to the where we are in the width of
 * the screen
 * @param mapx int value allways starts from zero for raycasting
 * @param mapy int value allways starts from zero for raycasting
 */
void	raycast_help(t_data *img, int x, int mapx, int mapy)
{
	t_loc	loc;

	init_local(&loc, x, mapx, mapy);
	raycast_help1(img, &loc);
	raycast_help2(img, &loc);
	raycast_help3(img, &loc);
	raycast_help4(img, &loc);
	raycast_help5(img, &loc);
	raycast_help6(img, &loc);
}

/**
 * @brief function which will do the entire raycasting process
 * we will while loop over untill x < Screen width and 
 * call raycast help , then we put image to the window using 
 * using mlx_put_image_to_window.
 * 
 * @param img data structure related to the graphical part of the game
 */
void	raycast(t_data *img)
{
	int	x;
	int	map_x;
	int	map_y;

	map_x = 0;
	map_y = 0;
	x = 0;
	while (x < SCREENWIDTH)
	{
		raycast_help(img, x, map_x, map_y);
		x++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}
