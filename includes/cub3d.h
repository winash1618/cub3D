/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:13:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 21:46:21 by mkaruvan         ###   ########.fr       */
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

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define SCREENWIDTH 1080
# define SCREENHEIGHT 960
# define ROTSPEED 0.1
# define WALKSPEED 0.185

enum	e_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

/*------------------------------------------------*/
typedef struct s_info
{
	struct s_info	*prev;
	char			*data; // path_to_the_west_texture
	// we need to check if the path is valid, else exit
	enum e_type type; // WE
	// for F and C, we need to check if the data is valid, else exit
	// check commas, split (,), check if num, check num  0 < 255.
	struct s_info *next; // not more than 6
} t_info;

typedef struct s_map
{
	struct s_map *prev;
	char *data; // 1, 0, [N, S, E, W] (only one of them should survive)
	// no new line after a line
	// each 0 should not have a space around it
	// each line should begin and end with 1
	struct s_map *next;
} t_map;

typedef struct s_parse
{
	t_info	*info;
	t_map	*map;
} t_parse;
/*------------------FT_INFO------------------*/
void	ft_error(int err);
void	ft_check_path(t_info *info, int *err);
/*------------------FT_INFO------------------*/
t_info	*ft_info_new(char *data, enum e_type type);
// t_info	*ft_info_new(char *data, enum e_type type, int *err);
void	ft_info_add_back(t_info **lst, t_info *new);
void	ft_info_add_front(t_info **lst, t_info *new);
void	ft_info_clear(t_info **lst);
void	ft_print_info(t_info *lst);
/*-------------------------------------------*/
/*------------------FT_MAP-------------------*/
t_map	*ft_map_new(char *data);
void	ft_map_add_back(t_map **lst, t_map *new);
void	ft_map_add_front(t_map **lst, t_map *new);
void	ft_map_clear(t_map **lst);
void	ft_print_map(t_map *lst);
/*-------------------------------------------*/
/*----------------FT_SET_INFO----------------*/
t_info	*ft_set_info(int fd, int *err);
void	ft_handle_info(char *line, t_info **info, int *err);
void	ft_free_tab(char **tab);
int		ft_check_info(char *line);
int		ft_type(char *str);
int		ft_is_map(char *line, int *err);
int		ft_valid_line(char *line, int i, int *err);
int		ft_tablen(char **tab);
int		ft_spaces(char *line);
int		ft_only_nums(char *str);
void	ft_valid_nums(char *str, int type, int *err);
char	*ft_rm_spaces(char *str);
/*-------------------------------------------*/
/*----------------FT_SET_MAP-----------------*/
t_map	*ft_set_map(int fd, int *err);
int		ft_is_valid_end(char *line);
int		ft_space_0(char *str, char *str1, char *str2, int i);
int		ft_check_data2(char *str, char *str1, char *str2);
int		ft_check_data(t_map *line, t_map *line1, t_map *line2);
int		ft_check_map(t_map *map);
void	ft_handle_map(t_map **map, char *tmp);
int		there_is_new_line(char *str);
int		ft_is_begmap(char *tmp);
int		ft_start_point(char *str);
int		ft_is_linemap(char *tmp);
void	ft_map_helper_2(char *line, char **tmp, int *end_map);
int		ft_map_helper_1(char **tmp, int *is_already_map, int *start_point, t_map **map);
int		ft_no_line(char **line, int fd, int *err, int *end_map);
int		ft_map_helper_3(char **line, int *err, int *is_already_map);
void	init_ft_set_map(t_map **map, int *is_already_map, int *start_point, int *end_map);
/*-------------------------------------------*/
/*-----------------------------------------------*/

typedef struct	s_data
{
	void			*img;
	void			*win;
	void			*mlx;
	void			*ptr[4];
	int				*texture[4];
	int				bpp[4];
	int				ll[4];
	int				en[4];
	char			*addr;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	char			**s;
	char			**i;
	int				buffer[SCREENHEIGHT][SCREENWIDTH];
	int				width[4];
	int				height[4];
	unsigned int	drawstart;
	unsigned int	drawend;
	int				floor_color;
	int				ceiling_color;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_loc
{
	unsigned int	y;
	double			camerax;
	double			raydirx;
	double			raydiry;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	double			wallx;
	double			step;
	double			texpos;
	int				x;
	int				mapx;
	int				mapy;
	int				lineheight;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				tex_x;
	int				tex_y;
	int				color;
}					t_loc;

/*-----------------------------------------------*/
int		ft_parsing(int ac, char **av, t_parse **parse);
void	ft_parse_clear(t_parse **parse);
/*-----------------------------------------------*/
void	raycast(t_data *img);
void	ft_error(int err);
char	***create_map(t_parse *data);
int		key_check(int keycode, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_exit(void);
void	raycast_help1(t_data *img, t_loc *loc);
void	raycast_help2(t_data *img, t_loc *loc);
void	raycast_help3(t_data *img, t_loc *loc);
void	raycast_help4(t_data *img, t_loc *loc);
void	raycast_help5(t_data *img, t_loc *loc);
void	init_local(t_loc *loc, int x, int mapx, int mapy);
void	ft_clear_maps(char ***tab);
void	check_name(char *str);
void	ft_map_organize(t_data *img, t_parse *parse);
void	ft_init_player(t_data *img);
void	ft_put_player(t_data *img);
void	ft_set_player_dir(t_data *img, int j, int k);
void	image_putter(t_data *img);
int		create_color(char *str);
#endif