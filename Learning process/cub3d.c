#include "minilibx/mlx.h"
#include <math.h>
#include <stdio.h>
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int height = 1080;
	int width = 1920;
	mlx = mlx_init();
	if (!mlx)
		exit(0);
	mlx_win = mlx_new_window(mlx, width, height, "Hello world!");
	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	double x = 0;
	double y = 0;
	int color = 0x00000000;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			color  = (color + (int)(0xFF * (x / width))) << 16;
			my_mlx_pixel_put(&img, x, y++,color);
		}
		x++;
	}
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}