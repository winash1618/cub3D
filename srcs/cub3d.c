/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:10:36 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/15 19:14:03 by mkaruvan         ###   ########.fr       */
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

/*------------------------------------------*/
int	ft_len_info(t_info *info)
{
	t_info	*tmp;
	int		len;

	len = 0;
	tmp = info;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
/*------------------------------------------*/

/*------------------------------------------*/
int	ft_len_map(t_map *map)
{
	t_map	*tmp;
	int		len;

	len = 0;
	tmp = map;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
/*------------------------------------------*/

/*------------------------------------------*/
char **ft_tab_map(t_map *map)
{
	char	**tab;
	t_map	*tmp;
	int		len_map;
	int		i;

	i = 0;
	tab = NULL;
	tmp = map;
	len_map = ft_len_map(map);
	tab = (char **)malloc(sizeof(char *) * (len_map + 1));
	if (!tab)
		return (NULL);
	while (i < len_map)
	{
		tab[i] = ft_strdup(tmp->data);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
/*------------------------------------------*/

/*------------------------------------------*/
char **ft_tab_info(t_info *info)
{
	char	**tab;
	t_info	*tmp;
	int		len_info;
	int		i;

	i = 0;
	tab = NULL;
	tmp = info;
	len_info = ft_len_info(info);
	tab = (char **)malloc(sizeof(char *) * (len_info + 1));
	if (!tab)
		return (NULL);
	while (i < len_info)
	{
		tab[i] = ft_strdup(tmp->data);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
/*------------------------------------------*/

/*------------------------------------------*/
char	***create_map(t_parse *data)
{
	char ***tab;

	tab = (char ***)malloc(sizeof(char **) * (2 + 1));
	tab[0] = ft_tab_info(data->info);
	tab[1] = ft_tab_map(data->map);
	tab[2] = NULL;
	return (tab);
}
/*------------------------------------------*/

/*------------------------------------------*/
void	ft_clear_maps(char ***tab)
{
	if (tab[0])
		ft_free_tab(tab[0]);
	if (tab[1])
		ft_free_tab(tab[0]);
	free(tab);
}
/*------------------------------------------*/
// char **create_map(t_parse *data)
// {
// 	int	fd;
// 	int	count;
// 	t_map *tmp;
// 	int	i;
// 	char **s;
	
// 	fd = 0;
// 	count = 0;
// 	s = NULL;
// 	tmp = data->map;
// 	while (tmp->next != NULL)
// 	{
// 		tmp = tmp->next;
// 		count++;
// 	}
// 	s = (char **)malloc((count + 1) * sizeof(char *));
// 	i = 0;
// 	while (data->map->next != NULL)
// 	{
// 		s[i] = ft_strdup(data->map->data);
// 		data->map = data->map->next;
// 		printf("fsdsdf\n");
// 	}
// 	s[count] = NULL;
	
// 	return (s);
// }

