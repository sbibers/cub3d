/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:38:55 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/08 19:20:09 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/ft_printf.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

char	*ft_strjoin_printf(t_printf *og_res, int count)
{
	t_printf	*tmp;
	char		*res;
	int			i;
	int			j;

	res = malloc(sizeof(char) * (count + 1));
	if (!res)
		return (NULL);
	i = 0;
	tmp = og_res;
	while (tmp)
	{
		j = 0;
		while (j < tmp->len)
			res[i++] = tmp->str[j++];
		tmp = tmp->next;
	}
	res[i] = '\0';
	return (res);
}
