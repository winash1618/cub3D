/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:50:17 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/05 19:33:19 by mkaruvan         ###   ########.fr       */
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

void init_local(t_loc *loc, int x, int mapX, int mapY)
{
	loc->x = x;
	loc->y = 0;
	loc->mapX = mapX;
	loc->mapY = mapY;
	loc->cameraX = 0;
	loc->rayDirX = 0;
	loc->rayDirY = 0;
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

void raycast_help1(t_data *img, t_loc *loc)
{
	//calculate ray position and direction
	loc->cameraX = 2 * loc->x / (double)(screenWidth) - 1; //x-coordinate in camera space
	loc->rayDirX = img->dirX + img->planeX * loc->cameraX;
	loc->rayDirY = img->dirY + img->planeY * loc->cameraX;
	//which box of the map we're in
	loc->mapX = (int)(img->posX);
	loc->mapY = (int)(img->posY);
	
	//length of ray from one x or y-side to next x or y-side
	loc->deltaDistX = (loc->rayDirX == 0) ? 1e30 : fabs(1 / loc->rayDirX);
	loc->deltaDistY = (loc->rayDirY == 0) ? 1e30 : fabs(1 / loc->rayDirY);
}

void raycast_help2(t_data *img, t_loc *loc)
{
	//calculate step and initial sideDist
	if (loc->rayDirX < 0)
	{
		loc->stepX = -1;
		loc->sideDistX = (img->posX - loc->mapX) * loc->deltaDistX;
	}
	else
	{
		loc->stepX = 1;
		loc->sideDistX = (loc->mapX + 1.0 - img->posX) * loc->deltaDistX;
	}
	if (loc->rayDirY < 0)
	{
		loc->stepY = -1;
		loc->sideDistY = (img->posY - loc->mapY) * loc->deltaDistY;
	}
	else
	{
		loc->stepY = 1;
		loc->sideDistY = (loc->mapY + 1.0 - img->posY) * loc->deltaDistY;
	}
}

void raycast_help3(t_data *img, t_loc *loc)
{
	//perform DDA
	while (loc->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (loc->sideDistX < loc->sideDistY)
		{
			loc->sideDistX += loc->deltaDistX;
			loc->mapX += loc->stepX;
			loc->side = 0;
		}
		else
		{
			loc->sideDistY += loc->deltaDistY;
			loc->mapY += loc->stepY;
			loc->side = 1;
		}
		// printf("%d %d\n", mapX, mapY);
		// fflush(stdout);
		//Check if ray has hit a wall
		if (ft_strlen(img->s[loc->mapX]) > loc->mapY)
			if (img->s[loc->mapX][loc->mapY] == '1')
				loc->hit = 1;
	} 
}

void raycast_help4(t_data *img, t_loc *loc)
{
	//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(loc->side == 0)
			loc->perpWallDist = (loc->sideDistX - loc->deltaDistX);
		else
			loc->perpWallDist = (loc->sideDistY - loc->deltaDistY);
		//Calculate height of line to draw on screen
		loc->lineHeight = (int)(screenHeight / loc->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		img->drawStart = -loc->lineHeight / 2 + screenHeight / 2;
		if(img->drawStart < 0)img->drawStart = 0;
			img->drawEnd = loc->lineHeight / 2 + screenHeight / 2;
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
		if (loc->side == 0) loc->wallX = img->posY + loc->perpWallDist * loc->rayDirY;
		else           loc->wallX = img->posX + loc->perpWallDist * loc->rayDirX;
		loc->wallX -= floor((loc->wallX));

		//x coordinate on the texture
		loc->texX = (int)(loc->wallX * (double)(texWidth));
		if(loc->side == 0 && loc->rayDirX > 0) loc->texX = texWidth - loc->texX - 1;
		if(loc->side == 1 && loc->rayDirY < 0) loc->texX = texWidth - loc->texX - 1;
		//give x and y sides different brightness
		// if (side == 1) {color = color / 2;}
}

void raycast_help5(t_data *img, t_loc *loc)
{
	//draw the pixels of the stripe as a vertical line
		loc->step = 1.0 * texHeight / loc->lineHeight;
      // Starting texture coordinate
      loc->texPos = (img->drawStart - screenHeight / 2 + loc->lineHeight / 2) * loc->step;
      for(loc->y = 0; loc->y < screenHeight; loc->y++)
      {
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		if (loc->y >= img->drawStart && loc->y <= img->drawEnd)
		{
			loc->texY = (int)loc->texPos & (img->height[0] - 1);
			loc->texPos += loc->step;
			// fflush(stdout);
			if (loc->side == 0 && loc->rayDirX > 0)
				loc->color = (int)img->texture[0][(int)texHeight * loc->texY + loc->texX];
			else if (loc->side == 0 && loc->rayDirX < 0)
				loc->color = (int)img->texture[1][(int)texHeight * loc->texY + loc->texX];
			else if (loc->side == 1 && loc->rayDirY > 0)
				loc->color = (int)img->texture[2][(int)texHeight * loc->texY + loc->texX];
			else if (loc->side == 1 && loc->rayDirY < 0)
				loc->color = (int)img->texture[3][(int)texHeight * loc->texY + loc->texX];
			
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// printf("%d %d %d %d\n", img->texture[texHeight * texY + texX], texHeight * texY + texX, texX, texY);
			if(loc->side == 1) loc->color = (loc->color >> 1) & 8355711;
			img->buffer[loc->y][loc->x] = loc->color;
		}
	  }
}

void raycast_help6(t_data *img, t_loc *loc)
{
	unsigned int i = 0;
	while (i < screenHeight)
	{
		if (i <  screenHeight / 2)
			my_mlx_pixel_put(img, loc->x, i, 0x00FF0000);
		else if (i >  screenHeight / 2)
			my_mlx_pixel_put(img, loc->x, i, 0x000000FF);
		i++;
	}
	i = 0;
	while (i < screenHeight)
	{
		if (i >= img->drawStart && i <= img->drawEnd)
		{
			my_mlx_pixel_put(img, loc->x, i,	img->buffer[i][loc->x]);
		}
		i++;
	}
}

void raycast_help(t_data *img, int x, int mapX, int mapY)
{
	t_loc loc;
	
	init_local(&loc, x, mapX, mapY);
	raycast_help1(img, &loc);
	raycast_help2(img, &loc);
	raycast_help3(img, &loc);
	raycast_help4(img, &loc);
	raycast_help5(img, &loc);
	raycast_help6(img, &loc);
}

void raycast(t_data *img)
{
	int x = 0;
	int mapX;
	int mapY;

	mapX = 0;
	mapY = 0;
	while (x < screenWidth)
	{
		raycast_help(img, x, mapX, mapY);
		x++;
	}
	printf("%u %u %d %d \n", img->drawStart, img->drawEnd, mapX, mapY);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}
