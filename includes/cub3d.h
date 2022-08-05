/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:05:13 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/05 16:31:43 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <unistd.h>

# define mapWidth 24
# define mapHeight 24
# define texWidth 64
# define texHeight 64
# define screenWidth 1080
# define screenHeight 960
# define rotspeed 0.1
# define walkspeed 0.185

typedef struct	s_data
{
	void	*img;
	void	*win;
	void	*mlx;
	void	*ptr[4];
	int		*texture[4];
	int		bpp[4];
	int		ll[4];
	int		en[4];
	char	*addr;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	char	**s;
	int	buffer[screenHeight][screenWidth];
	int width[4];
	int height[4];
	// double	cameraX;
	// double	rayDirX;
	// double	rayDirY;
	unsigned int	drawStart;
	unsigned int	drawEnd;
	
	
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void raycast(t_data *img);
char **create_map(int ac, char **av);
int	key_check(int keycode, t_data *img);

#endif