/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:24:47 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/02 12:58:45 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "minilibx/mlx.h"
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
int	ft_exit(void)
{
	exit (1);
	return (0);
}
typedef struct	s_data
{
	void	*img;
	void	*win;
	void	*mlx;
	char	*addr;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	char	**s;
	// double	cameraX;
	// double	rayDirX;
	// double	rayDirY;
	int		drawStart;
	int		drawEnd;
	
	
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
void raycast(t_data *img);

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
	int line_num;
	char *str;
	int count = 0;
	char **s;
	str = NULL;
	int i;
	if (ac == 2)
	{
		check_name(av[1]);
		fd = open(ft_strjoin("./map/", av[1], 0), O_RDONLY);
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
int	key_check(int keycode, t_data *img)
{
	if (keycode == 123)
	{
		if(img->s[(int)(img->posX + img->dirX)][(int)(img->posY)] == false)
			img->posX += img->dirX;
		if(img->s[(int)(img->posX)][(int)(img->posY + img->dirY)] == false)
			img->posY += img->dirY;
		raycast(img);
	}
	else if (keycode == 124)
	{
      if(img->s[(int)(img->posX - img->dirX)][(int)(img->posY)] == false) img->posX -= img->dirX;
      if(img->s[(int)(img->posX)][(int)(img->posY - img->dirY)] == false) img->posY -= img->dirY;
    	raycast(img);
	}
	else if (keycode == 125)
	{
      //both camera direction and camera plane must be rotated
      double oldDirX = img->dirX;
      img->dirX = img->dirX- img->dirY;
      img->dirY = oldDirX + img->dirY;
      double oldPlaneX = img->planeX;
      img->planeX = img->planeX- img->planeY;
      img->planeY = oldPlaneX + img->planeY;
    	raycast(img);
	}
	else if (keycode == 126)
	 {
      //both camera direction and camera plane must be rotated
      double oldDirX = img->dirX;
      img->dirX = img->dirX - img->dirY;
      img->dirY = oldDirX + img->dirY;
      double oldPlaneX = img->planeX;
      img->planeX = img->planeX - img->planeY;
      img->planeY = oldPlaneX + img->planeY;
    	raycast(img);
	}
	return (0);
}
void raycast(t_data *img)
{
	
	int x = 0;
	while (x < screenWidth)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(screenWidth) - 1; //x-coordinate in camera space
		double rayDirX = img->dirX + img->planeX * cameraX;
		double rayDirY = img->dirY + img->planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)(img->posX);
		int mapY = (int)(img->posY);

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
		if(img->drawEnd >= screenHeight)img->drawEnd = screenHeight - 1;
		//choose wall color
		int color;
		switch(img->s[mapX][mapY])
		{
			case '1':  color = 0x00FF0000;  break; //red
			case '0':  color = 0x00FFFF00;  break; //green
			case 'N':  color = 0x0000FF00;   break; //blue
			default: color = 0x000000FF; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		int i = img->drawStart;
		while (i < img->drawEnd)
		{
			my_mlx_pixel_put(img, x, i, color);
			i++;
		}
		
		x++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}
int main(int ac, char **av)
{
	t_data	img;
	img.mlx = mlx_init();
	if (!img.mlx)
		exit(0);
	img.s = create_map(ac, av);
	printf("%s\n", img.s[0]);
	img.win = mlx_new_window(img.mlx, screenWidth, screenHeight, "Hello world!");
	img.img = mlx_new_image(img.mlx,screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	img.posX = 3;
	img.posY = 29;  //x and y start position
	img.dirX = -1;
	img.dirY = 0; //initial direction vector
	img.planeX = 0;
	img.planeY = 0.66; //the 2d raycaster version of camera plane
	int x = 0;
	while (x < screenWidth)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(screenWidth) - 1; //x-coordinate in camera space
		double rayDirX = img.dirX + img.planeX * cameraX;
		double rayDirY = img.dirY + img.planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)(img.posX);
		int mapY = (int)(img.posY);

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
			sideDistX = (img.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - img.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (img.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - img.posY) * deltaDistY;
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
			if (ft_strlen(img.s[mapX]) > mapY)
				if (img.s[mapX][mapY] == '1')
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
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;
		//choose wall color
		int color;
		switch(img.s[mapX][mapY])
		{
			case '1':  color = 0x00FF0000;  break; //red
			case '0':  color = 0x00FFFF00;  break; //green
			case 'N':  color = 0x0000FF00;   break; //blue
			default: color = 0x000000FF; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		int i = drawStart;
		while (i < drawEnd)
		{
			my_mlx_pixel_put(&img, x, i, color);
			i++;
		}
		
		x++;
	}
	// mlx_hook(img.img, 17, 1L << 17, ft_exit, 0);
	// printf("hi");
	// fflush(stdout);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, 2, 0, key_check, &img);
	mlx_loop(img.mlx);
	return (0);
}