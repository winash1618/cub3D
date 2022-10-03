/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:13:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/03 10:28:47 by mkaruvan         ###   ########.fr       */
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

enum	e_info_type
{
	WE, EA, SO, NO, F, C
};

/*----------------------------*/
typedef struct s_info
{
	// t_info *prev;
	char *data; // path_to_the_west_texture
	// we need to check if the path is valid, else exit
	enum e_info_type type; // WE
	// for F and C, we need to check if the data is valid, else exit
	// check commas, split (,), check if num, check num  0 < 255.
	t_info *next; // not more than 6
} t_info;

typedef struct s_map
{
	t_map *prev;
	char *data; // 1, 0, [N, S, E, W] (only one of them should survive)
	// no new line after a line
	// 
	// each line should begin and end with 1
	t_map *next;
} t_map;

typedef struct s_parse
{
	t_info	*info;
	t_map	*map;
} t_parse;
/*----------------------------*/

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

typedef struct s_loc
{
	int x;
	unsigned int y;
	int mapX;
	int mapY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int lineHeight;
	int stepX;
	int stepY;
	int hit;
	int side;
	double wallX;
	int texX;
	int texY;
	double step;
	double texPos;
	int color;
}	t_loc;

void raycast(t_data *img);
char **create_map(int ac, char **av);
int	key_check(int keycode, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif