/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:10:36 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/11/10 15:14:12 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief find the number of nodes in info
 * 
 * @param info linked list related to map info
 * @return int number of nodes
 */
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

/**
 * @brief find the height of the map.
 * 
 * @param map linked list related to parsed map.
 * @return int map height
 */
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

/**
 * @brief convert linked list related to parsed map to double array
 * 
 * @param map linked list related to parsed map
 * @return char** double array contains parsed map
 */
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

/**
 * @brief convert linked list in info to double array
 * 
 * @param info linked list related to parsing info.
 * @return char** double array contains parsing info.
 */
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

/**
 * @brief convert parsed data in linked list to two double string array
 * and save its address in an array.
 * 
 * @param data data structure related to the parsing
 * @return char*** pointer to the first element of the array that contain 
 * two double array.
 */
char	***create_map(t_parse *data)
{
	char	***tab;

	tab = (char ***)malloc(sizeof(char **) * (2 + 1));
	tab[0] = ft_tab_info(data->info);
	tab[1] = ft_tab_map(data->map);
	tab[2] = NULL;
	return (tab);
}
