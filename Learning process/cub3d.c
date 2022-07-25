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

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	int x = 200;
	int y = 300;
	int z = 300;
	while (x <= 600)
	{
		if (x < 300)
		{
			my_mlx_pixel_put(&img, x, y++, 0x00FF0000);
			my_mlx_pixel_put(&img, x, z--, 0x00FF0000);
		}
		if (x >= 300 && x <= 500)
		{
		my_mlx_pixel_put(&img, x, 400, 0x00FF0000);
		my_mlx_pixel_put(&img, x, 200, 0x00FF0000);

		}
		if (x >500 )
		{
			my_mlx_pixel_put(&img, x, y--, 0x00FF0000);
			my_mlx_pixel_put(&img, x, z++, 0x00FF0000);
		}
		x++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}