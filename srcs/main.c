/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:11:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/16 08:11:26 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int create_color(char *str)
{
	char **s = ft_split(str, ',');
	int a[3];
	int i = 0;
	while (s[i])
	{
		a[i] = ft_atoi(s[i]);
		free(s[i]);
		i++;
	}
	free (s);
	return create_trgb(0, a[0], a[1], a[2]);
}


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
		img->dirX = -1;
		img->planeY = 0.66;
	}
	else if (img->s[j][k] == 'E')
	{
		img->dirY = -1;
		img->planeX = -0.66;
	}
	else if (img->s[j][k] == 'W')
	{
		img->dirY = 1;
		img->planeX = -0.66;
	}
	else
	{
		img->dirX = 1;
		img->planeY = 0.66;
	}
}

void	ft_put_player(t_data *img)
{
	int j = 0;
	int k = 0;
	
	while (img->s[j])
	{
		k = 0;
		while(img->s[j][k])
		{
			if (img->s[j][k] == 'W' || img->s[j][k] == 'N' || img->s[j][k] == 'S' || img->s[j][k] == 'E')
			{
				img->posX = j;
				img->posY = k;
				ft_set_player_dir(img, j, k);
				break;
			}
			k++;
		}
		j++;
	}
}

void	ft_init_player(t_data *img)
{
	img->posX = 0;
	img->posY = 0; //x and y start position
	img->dirX = 0;
	img->dirY = 0; //initial direction vector
	img->planeX = 0;
	img->planeY = 0; //the 2d raycaster version of camera plane
	img->drawStart = 0;
	img->drawEnd = 0;
}

void ft_map_organize(t_data *img, t_parse *parse)
{
	char ***p;

	p = create_map(parse);
	ft_parse_clear(&parse);
	img->i = p[0];
	img->s = p[1];
	img->floor_color = create_color(img->i[F]);
	img->ceiling_color = create_color(img->i[C]);
	free(p);
}

void	ft_error(int err)
{
	(void)err;
	exit(1);
}

int main(int ac, char **av)
{
	int		err;
	t_parse	*parse;
	t_data	img;

	err = 0;
	parse = NULL;
	err = ft_parsing(ac, av, &parse);
	if (err)
		ft_error(err);
	ft_map_organize(&img, parse);
	ft_init_player(&img);
	ft_put_player(&img);
	img.mlx = mlx_init();
	if (!img.mlx)
		exit(0);
	img.win = mlx_new_window(img.mlx, screenWidth, screenHeight, "cub3D");
	img.img = mlx_new_image(img.mlx,screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	image_putter(&img);
	fflush(stdout);
	raycast(&img);
	mlx_hook(img.win, 2, 0, key_check, &img);
	mlx_hook(img.win, 17, 1L << 17, ft_exit, 0);
	mlx_loop(img.mlx);
	return (0);
}