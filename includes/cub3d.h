/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:13:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 13:55:29 by mkaruvan         ###   ########.fr       */
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
	char			*data;
	enum e_type		type;
	struct s_info	*next;
}					t_info;

typedef struct s_map
{
	struct s_map	*prev;
	char			*data;
	struct s_map	*next;
}					t_map;

typedef struct s_parse
{
	t_info	*info;
	t_map	*map;
}			t_parse;
typedef struct s_file
{
	struct s_file	*prev;
	char			*line;
	struct s_file	*next;
}				t_file;

/*------------------FT_SAVE_FILE------------------*/
t_file	*ft_save_file(char *str, int *err);
t_file	*ft_file_new(char *line);
void	ft_file_add_back(t_file **lst, t_file *new);
void	ft_file_add_front(t_file **lst, t_file *new);
void	ft_file_clear(t_file **lst);
void	ft_file_print(t_file *lst);
t_file	*ft_clean_file(t_file *file);
int		ft_spaces(char *line);
t_file	*ft_making_file(char *str, int *err);
/*------------------FT_SAVE_FILE------------------*/

/*----------------FT_SET_INFO---------------------*/
t_file	*ft_save_info(t_file *file);
int		ft_line_digit(char *line);
t_info	*ft_set_info(t_file *file, int *err);
void	ft_free_tab(char **tab);
int		ft_type(char *str);
int		ft_tablen(char **tab);
int		check_info(t_info *info);
int		ft_line_digit(char *line);
t_file	*ft_save_info(t_file *file);
int		ft_only_nums(char *str);
int		ft_valid_nums(char *str, int type);
int		ft_check_path_part(char *str);
int		ft_check_path(t_info *info);
int		check_types_3(t_info *info);
int		nb_comas(char *str);
/*------------------------------------------------*/

/*----------------FT_SET_MAP---------------------*/
t_map	*ft_set_map(t_file *map_file);
t_file	*ft_save_map(t_file *file);
int		valid_line_map(char *line);
int		ft_valid_map(t_file *file);
int		empty_space(char *str);
int		all_spaces(char *line);
int		start_pos(char *str);
int		start_end_well(char *line);
int		check_first_last(t_file *file);
int		ft_space_0(char *str, int i);
int		ft_space_0_part(char *str, int i);
int		check_zero(t_file *file);
/*------------------------------------------------*/

/*------------------FT_INFO------------------*/
t_info	*ft_info_new(char *data, enum e_type type);
void	ft_info_add_back(t_info **lst, t_info *new);
void	ft_info_add_front(t_info **lst, t_info *new);
void	ft_info_clear(t_info **lst);
void	ft_print_info(t_info *lst);
int		ft_info_len(t_info *lst);
/*-------------------------------------------*/
/*------------------FT_MAP-------------------*/
t_map	*ft_map_new(char *data);
void	ft_map_add_back(t_map **lst, t_map *new);
void	ft_map_add_front(t_map **lst, t_map *new);
void	ft_map_clear(t_map **lst);
void	ft_print_map(t_map *lst);
/*-------------------------------------------*/

typedef struct s_data
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
int		ft_parser(char *av, t_parse **parse);
int		ft_parsing(int ac, char **av, t_parse **parse);
void	ft_parse_clear(t_parse **parse);
/*-----------------------------------------------*/
void	raycast(t_data *img);
char	***create_map(t_parse *data);
int		key_check(int keycode, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_exit(t_data *img);
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