/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:11:48 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:16:54 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_help7(t_data *img, t_loc *loc)
{
	loc->step = 1.0 * TEXHEIGHT / loc->lineHeight;
	loc->texPos = (img->drawStart - SCREENHEIGHT / 2
			+ loc->lineHeight / 2) * loc->step;
	loc->y = 0;
}

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
		if (i >= img->drawStart && i <= img->drawEnd)
		{
			my_mlx_pixel_put(img, loc->x, i, img->buffer[i][loc->x]);
		}
		i++;
	}
}

void	raycast_help5(t_data *img, t_loc *loc)
{
	raycast_help7(img, loc);
	while (loc->y < SCREENHEIGHT)
	{
		if (loc->y >= img->drawStart && loc->y <= img->drawEnd)
		{
			loc->texY = (int)loc->texPos & (img->height[0] - 1);
			loc->texPos += loc->step;
			if (loc->side == 0 && loc->rayDirX > 0)
				loc->color = (int)img->texture[0][(int)
					TEXHEIGHT * loc->texY + loc->texX];
			else if (loc->side == 0 && loc->rayDirX < 0)
				loc->color = (int)img->texture[1][(int)
					TEXHEIGHT * loc->texY + loc->texX];
			else if (loc->side == 1 && loc->rayDirY > 0)
				loc->color = (int)img->texture[2][(int)
					TEXHEIGHT * loc->texY + loc->texX];
			else if (loc->side == 1 && loc->rayDirY < 0)
				loc->color = (int)img->texture[3][(int)
					TEXHEIGHT * loc->texY + loc->texX];
			if (loc->side == 1)
				loc->color = (loc->color >> 1) & 8355711;
			img->buffer[loc->y][loc->x] = loc->color;
		}
		loc->y++;
	}
}

void	raycast_help(t_data *img, int x, int mapX, int mapY)
{
	t_loc	loc;

	init_local(&loc, x, mapX, mapY);
	raycast_help1(img, &loc);
	raycast_help2(img, &loc);
	raycast_help3(img, &loc);
	raycast_help4(img, &loc);
	raycast_help5(img, &loc);
	raycast_help6(img, &loc);
}

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
