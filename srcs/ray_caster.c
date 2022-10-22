/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:11:48 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:42:10 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_help7(t_data *img, t_loc *loc)
{
	loc->step = 1.0 * TEXHEIGHT / loc->lineheight;
	loc->texpos = (img->drawstart - SCREENHEIGHT / 2
			+ loc->lineheight / 2) * loc->step;
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
		if (i >= img->drawstart && i <= img->drawend)
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
