/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:10:36 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/10/22 20:39:58 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
char	**ft_tab_map(t_map *map)
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
char	**ft_tab_info(t_info *info)
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
		tab[tmp->type] = ft_strdup(tmp->data);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	***create_map(t_parse *data)
{
	char	***tab;

	tab = (char ***)malloc(sizeof(char **) * (2 + 1));
	tab[0] = ft_tab_info(data->info);
	tab[1] = ft_tab_map(data->map);
	tab[2] = NULL;
	return (tab);
}
