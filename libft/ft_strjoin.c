/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:35:16 by ayassin           #+#    #+#             */
/*   Updated: 2022/08/05 16:15:36 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Join string "s2" to "s1" in a new string "temp" and returns it
**malloc DANGER**/
char	*ft_strjoin(char *s1, char *s2, int flag)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[i] = '\0';
	}
	new = (char *)malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!new)
		return (0);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	if (flag)
		free (s1);
	return (new);
}
