/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:11:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/15 19:01:40 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	image_putter(t_data *img)
{
	img->ptr[0] = mlx_xpm_file_to_image(img->mlx, "./img/redbrick.xpm",
			&img->width[0], &img->height[0]);
	img->texture[0] = (int (*))mlx_get_data_addr(img->ptr[0],
			&img->bpp[0], &img->ll[0], &img->en[0]);
	img->ptr[1] = mlx_xpm_file_to_image(img->mlx, "./img/wood.xpm",
			&img->width[1], &img->height[1]);
	img->texture[1] = (int (*))mlx_get_data_addr(img->ptr[1],
			&img->bpp[1], &img->ll[1], &img->en[1]);
	img->ptr[2] = mlx_xpm_file_to_image(img->mlx, "./img/barrel.xpm",
			&img->width[2], &img->height[2]);
	img->texture[2] = (int (*))mlx_get_data_addr(img->ptr[2],
			&img->bpp[2], &img->ll[2], &img->en[2]);
	img->ptr[3] = mlx_xpm_file_to_image(img->mlx, "./img/bluestone.xpm",
			&img->width[3], &img->height[3]);
	img->texture[3] = (int (*))mlx_get_data_addr(img->ptr[3], &img->bpp[3],
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
	img.mlx = mlx_init();
	if (!img.mlx)
		exit(0);

	char ***p;
	p = create_map(parse);
	img.s = p[1];
	
	printf("hello\n");
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
	while(img.s[j])
	{
		printf("%s", img.s[j]);
		fflush(stdout);
		j++;
	}
	j = 0;
	while (img.s[j])
	{
		printf("%s", img.s[j]);
		k = 0;
		while(img.s[j][k])
		{
			printf("%c %d\n", img.s[j][k], k);
			
			if (img.s[j][k] == 'P' || img.s[j][k] == 'N' || img.s[j][k] == 'S' || img.s[j][k] == 'E')
			{
				img.posX = j;
				img.posY = k;
				if (img.s[j][k] == 'N')
				{
					img.dirX = -1;
					img.dirY = 0;
					img.planeX = 0;
					img.planeY = 0.66;
				}
				else if (img.s[j][k] == 'P')
				{
					img.dirX = 0;
					img.dirY = -1;
					img.planeX = -0.66;
					img.planeY = 0;
				}
				else if (img.s[j][k] == 'E')
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
			printf("hi0 ");
			k++;
		}
		j++;
	}
	
	image_putter(&img);
	
	printf("%f %f \n", img.posX, img.posY);
	fflush(stdout);
	
	raycast(&img);
	mlx_hook(img.win, 2, 0, key_check, &img);
	mlx_loop(img.mlx);
	
	/*----------------------------------------------------------------*/
	return (0);
}