/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:11:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/16 06:57:02 by mkaruvan         ###   ########.fr       */
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
			&img->width[0], &img->height[0]);
	img->texture[NO] = (int (*))mlx_get_data_addr(img->ptr[NO],
			&img->bpp[0], &img->ll[0], &img->en[0]);
	img->ptr[SO] = mlx_xpm_file_to_image(img->mlx, img->i[SO],
			&img->width[1], &img->height[1]);
	img->texture[SO] = (int (*))mlx_get_data_addr(img->ptr[SO],
			&img->bpp[1], &img->ll[1], &img->en[1]);
	img->ptr[WE] = mlx_xpm_file_to_image(img->mlx, img->i[WE],
			&img->width[2], &img->height[2]);
	img->texture[WE] = (int (*))mlx_get_data_addr(img->ptr[WE],
			&img->bpp[2], &img->ll[2], &img->en[2]);
	img->ptr[EA] = mlx_xpm_file_to_image(img->mlx, img->i[EA],
			&img->width[3], &img->height[3]);
	img->texture[EA] = (int (*))mlx_get_data_addr(img->ptr[EA], &img->bpp[3],
			&img->ll[3], &img->en[3]);
}

int main(int ac, char **av)
{
	// int		err;
	t_parse	*parse;
	t_data	img;
	int j = 0;
	int k = 0;

	// err = 0;
	parse = NULL;
	ft_parsing(ac, av, &parse);

	char ***p;
	p = create_map(parse);
	img.s = p[1];
	img.i = p[0];
	while(img.i[j])
	{
		printf("%s\n", img.i[SO]);
		fflush(stdout);
		j++;
	}
	j = 0;
	img.floor_color = create_color(img.i[F]);
	img.ceiling_color = create_color(img.i[C]);
	img.mlx = mlx_init();
	if (!img.mlx)
		exit(0);
	

	
	// ft_parse_clear(&parse);
	img.win = mlx_new_window(img.mlx, screenWidth, screenHeight, "Hello world!");
	img.img = mlx_new_image(img.mlx,screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	img.posX = 3;
	img.posY = 29; //x and y start position
	img.dirX = 0;
	img.dirY = -1; //initial direction vector
	img.planeX = -0.66;
	img.drawStart = 0;
	img.drawEnd = 0;
	img.planeY = 0; //the 2d raycaster version of camera plane
	// while(img.s[j])
	// {
	// 	printf("%s", img.s[j]);
	// 	fflush(stdout);
	// 	j++;
	// }
	j = 0;
	
	while (img.s[j])
	{
		k = 0;
		while(img.s[j][k])
		{
			if (img.s[j][k] == 'W' || img.s[j][k] == 'N' || img.s[j][k] == 'S' || img.s[j][k] == 'E')
			{
				img.posX = j;
				img.posY = k;
				if (img.s[j][k] == 'S')
				{
					img.dirX = -1;
					img.dirY = 0;
					img.planeX = 0;
					img.planeY = 0.66;
				}
				else if (img.s[j][k] == 'E')
				{
					img.dirX = 0;
					img.dirY = -1;
					img.planeX = -0.66;
					img.planeY = 0;
				}
				else if (img.s[j][k] == 'W')
				{
					img.dirX = 0;
					img.dirY = 1;
					img.planeX = -0.66;
					img.planeY = 0;
				}
				else
				{
					img.dirX = 1;
					img.dirY = 0;
					img.planeX = 0;
					img.planeY = 0.66;
				}
				break;
			}
			// printf("hi0 ");
			k++;
		}
		j++;
	}
	
	image_putter(&img);
	
	// printf("%f %f \n", img.posX, img.posY);
	fflush(stdout);
	
	raycast(&img);
	mlx_hook(img.win, 2, 0, key_check, &img);
	mlx_loop(img.mlx);
	
	/*----------------------------------------------------------------*/
	return (0);
}