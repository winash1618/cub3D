/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:50:17 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/05 17:23:14 by mkaruvan         ###   ########.fr       */
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
	*(unsigned int*)dst = color;
}
static int	isforbchar(char a, char const *set)
{
	if (set)
	{
		while (*set)
		{
			if (a == *set)
				return (1);
			set++;
		}
	}
	return (0);
}
char	*ft_strtrim(char const *s1, char const *set)
{
	int		pos;
	int		len;
	char	*temp;

	pos = 0;
	if (!s1)
		return (0);
	while (*s1 && isforbchar(*s1, set))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && isforbchar(s1[len - 1], set))
		len--;
	temp = (char *)malloc((len + 1) * sizeof(char));
	if (!temp)
		return (0);
	while (pos < len)
	{
		temp[pos] = s1[pos];
		pos++;
	}
	temp[pos] = 0;
	return (temp);
}
void check_name(char *str)
{
	while(*str)
	{
		if(*str == '.')
		{
			if (strcmp(str + 1, "cub"))
			{
				exit(EXIT_FAILURE);
			}
			else
				break;
		}
		str++;
	}
}
char **create_map(int ac, char **av)
{
	int fd;
	// int line_num;
	fd = 0;
	char *str;
	int count = 0;
	char **s;
	s = NULL;
	str = NULL;
	int i;
	if (ac == 2)
	{
		fd = open(ft_strjoin("./map/", av[1], 0), O_RDONLY);
		check_name(av[1]);
		str = get_next_line(fd);
		count++;
		if (!str)
			return (0);
		else
		{
			while (str)
			{
				str = get_next_line(fd);
				count++;
			}
		}
		close (fd);
		fd = open(ft_strjoin("./map/", av[1], 0), O_RDONLY);
		
		s = (char **)malloc(sizeof(char *) * (count));
		i = 0;
		while (i < count)
		{
			s[i] = ft_strtrim(get_next_line(fd), "\n");
			i++;
		}
	}
	close(fd);
	i = 0;
	return (s);
}

void raycast(t_data *img)
{
	int x = 0;
	int mapX;
	int mapY;
	while (x < screenWidth)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(screenWidth) - 1; //x-coordinate in camera space
		double rayDirX = img->dirX + img->planeX * cameraX;
		double rayDirY = img->dirY + img->planeY * cameraX;
		//which box of the map we're in
		mapX = (int)(img->posX);
		mapY = (int)(img->posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (img->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - img->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (img->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - img->posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// printf("%d %d\n", mapX, mapY);
			// fflush(stdout);
			//Check if ray has hit a wall
			if (ft_strlen(img->s[mapX]) > mapY)
				if (img->s[mapX][mapY] == '1')
					hit = 1;
		} 
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		img->drawStart = -lineHeight / 2 + screenHeight / 2;
		if(img->drawStart < 0)img->drawStart = 0;
			img->drawEnd = lineHeight / 2 + screenHeight / 2;
		if(img->drawEnd >= screenHeight)
			img->drawEnd = screenHeight - 1;
		if(img->drawStart >= screenHeight)
			img->drawStart = 0;
		//choose wall color
		// int color;
		// switch(img->s[mapX][mapY])
		// {
		// 	case '1':  color = 0x00FF0000;  break; //red
		// 	default: color = 0x00000000; break; //yellow
		// }
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = img->posY + perpWallDist * rayDirY;
		else           wallX = img->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
		//give x and y sides different brightness
		// if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (img->drawStart - screenHeight / 2 + lineHeight / 2) * step;
      for(unsigned int y = 0; y < screenHeight; y++)
      {
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		if (y >= img->drawStart && y <= img->drawEnd)
		{
			int texY = (int)texPos & (img->height[0] - 1);
			texPos += step;
			// fflush(stdout);
			int color;
			if (side == 0 && rayDirX > 0)
				color = (int)img->texture[0][(int)texHeight * texY + texX];
			else if (side == 0 && rayDirX < 0)
				color = (int)img->texture[1][(int)texHeight * texY + texX];
			else if (side == 1 && rayDirY > 0)
				color = (int)img->texture[2][(int)texHeight * texY + texX];
			else if (side == 1 && rayDirY < 0)
				color = (int)img->texture[3][(int)texHeight * texY + texX];
			
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// printf("%d %d %d %d\n", img->texture[texHeight * texY + texX], texHeight * texY + texX, texX, texY);
			if(side == 1) color = (color >> 1) & 8355711;
			img->buffer[y][x] = color;
		}
		// else if (y < img->drawStart)
		// 	img->buffer[y][x] = 0x00FF0000;
		// else if (y > img->drawEnd)
		// 	img->buffer[y][x] = 0x00FF0000;
		
      }
		unsigned int i = 0;
		while (i < screenHeight)
		{
			if (i <  screenHeight / 2)
				my_mlx_pixel_put(img, x, i, 0x00FF0000);
			else if (i >  screenHeight / 2)
				my_mlx_pixel_put(img, x, i, 0x000000FF);
			i++;
		}
		i = 0;
		while (i < screenHeight)
		{
			if (i >= img->drawStart && i <= img->drawEnd)
			{
				my_mlx_pixel_put(img, x, i,	img->buffer[i][x]);
			}
			i++;
		}
		x++;
	}
	printf("%u %u %d %d \n", img->drawStart, img->drawEnd, mapX, mapY);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}
