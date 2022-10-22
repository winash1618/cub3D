/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_play.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:39:05 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:31:17 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	image_putter(t_data *img)
{
	img->ptr[NO] = mlx_xpm_file_to_image(img->mlx, img->i[NO],
			&img->width[NO], &img->height[NO]);
	img->texture[NO] = (int (*))mlx_get_data_addr(img->ptr[NO],
			&img->bpp[NO], &img->ll[NO], &img->en[NO]);
	img->ptr[SO] = mlx_xpm_file_to_image(img->mlx, img->i[SO],
			&img->width[SO], &img->height[SO]);
	img->texture[SO] = (int (*))mlx_get_data_addr(img->ptr[SO],
			&img->bpp[SO], &img->ll[SO], &img->en[SO]);
	img->ptr[WE] = mlx_xpm_file_to_image(img->mlx, img->i[WE],
			&img->width[WE], &img->height[WE]);
	img->texture[WE] = (int (*))mlx_get_data_addr(img->ptr[WE],
			&img->bpp[WE], &img->ll[WE], &img->en[WE]);
	img->ptr[EA] = mlx_xpm_file_to_image(img->mlx, img->i[EA],
			&img->width[EA], &img->height[EA]);
	img->texture[EA] = (int (*))mlx_get_data_addr(img->ptr[EA], &img->bpp[EA],
			&img->ll[EA], &img->en[EA]);
}

void	ft_set_player_dir(t_data *img, int j, int k)
{
	if (img->s[j][k] == 'S')
	{
		img->dirx = -1;
		img->planey = 0.66;
	}
	else if (img->s[j][k] == 'E')
	{
		img->diry = -1;
		img->planex = -0.66;
	}
	else if (img->s[j][k] == 'W')
	{
		img->diry = 1;
		img->planex = -0.66;
	}
	else
	{
		img->dirx = 1;
		img->planey = 0.66;
	}
}

void	ft_put_player(t_data *img)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (img->s[j])
	{
		k = 0;
		while (img->s[j][k])
		{
			if (img->s[j][k] == 'W' || img->s[j][k] == 'N'
				|| img->s[j][k] == 'S' || img->s[j][k] == 'E')
			{
				img->posx = j;
				img->posy = k;
				ft_set_player_dir(img, j, k);
				break ;
			}
			k++;
		}
		j++;
	}
}

void	ft_init_player(t_data *img)
{
	img->posx = 0;
	img->posy = 0;
	img->dirx = 0;
	img->diry = 0;
	img->planex = 0;
	img->planey = 0;
	img->drawstart = 0;
	img->drawend = 0;
}

void	ft_map_organize(t_data *img, t_parse *parse)
{
	char	***p;

	p = create_map(parse);
	ft_parse_clear(&parse);
	img->i = p[0];
	img->s = p[1];
	img->floor_color = create_color(img->i[F]);
	img->ceiling_color = create_color(img->i[C]);
	free(p);
}
