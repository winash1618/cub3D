/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:21:13 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:42:10 by mkaruvan         ###   ########.fr       */
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

void	init_local(t_loc *loc, int x, int mapx, int mapy)
{
	loc->x = x;
	loc->y = 0;
	loc->mapx = mapx;
	loc->mapy = mapy;
	loc->camerax = 0;
	loc->raydirx = 0;
	loc->raydiry = 0;
	loc->sidedistx = 0;
	loc->sidedisty = 0;
	loc->deltadistx = 0;
	loc->deltadisty = 0;
	loc->perpwalldist = 0;
	loc->lineheight = 0;
	loc->stepx = 0;
	loc->stepy = 0;
	loc->hit = 0;
	loc->side = 0;
	loc->wallx = 0;
	loc->tex_x = 0;
	loc->tex_y = 0;
	loc->step = 0;
	loc->texpos = 0;
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
