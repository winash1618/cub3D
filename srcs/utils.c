/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:21:13 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:28:08 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(void)
{
	exit (1);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_local(t_loc *loc, int x, int mapX, int mapY)
{
	loc->x = x;
	loc->y = 0;
	loc->mapX = mapX;
	loc->mapY = mapY;
	loc->cameraX = 0;
	loc->raydirx = 0;
	loc->raydiry = 0;
	loc->sideDistX = 0;
	loc->sideDistY = 0;
	loc->deltaDistX = 0;
	loc->deltaDistY = 0;
	loc->perpWallDist = 0;
	loc->lineHeight = 0;
	loc->stepX = 0;
	loc->stepY = 0;
	loc->hit = 0;
	loc->side = 0;
	loc->wallX = 0;
	loc->texX = 0;
	loc->texY = 0;
	loc->step = 0;
	loc->texPos = 0;
	loc->color = 0;
}

void	ft_clear_maps(char ***tab)
{
	if (tab[0])
		ft_free_tab(tab[0]);
	if (tab[1])
		ft_free_tab(tab[0]);
	free(tab);
}

void	check_name(char *str)
{
	while (*str)
	{
		if (*str == '.')
		{
			if (strcmp(str + 1, "cub"))
			{
				exit(EXIT_FAILURE);
			}
			else
				break ;
		}
		str++;
	}
}
