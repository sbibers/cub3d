/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:40:42 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/25 21:08:49 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	int			check;
	const char	*res;

	i = 0;
	check = 0;
	while (i - 1 < 0 || s[i - 1])
	{
		if (s[i] == (char)c)
		{
			res = &s[i];
			check = 1;
		}
		i++;
	}
	if (check == 0)
		return (0);
	return ((char *)res);
}
