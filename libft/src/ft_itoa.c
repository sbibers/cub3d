/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:34:40 by aatieh            #+#    #+#             */
/*   Updated: 2025/03/17 23:02:21 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	allocation(long int n, char **res, int base)
{
	int			i;

	i = 1;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	else if (n == 0)
		i++;
	while (n > 0)
	{
		n /= base;
		i++;
	}
	*res = (char *)malloc(sizeof(char) * i);
	return (i - 1);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			i;
	long int	temp;

	i = allocation((int)n, &res, 10);
	if (res == NULL)
		return (NULL);
	temp = n;
	if (n < 0)
	{
		temp *= -1;
		res[0] = '-';
	}
	res[i--] = '\0';
	if (temp == 0)
		res[i] = '0';
	while (temp > 0)
	{
		res[i--] = (temp % 10) + '0';
		temp /= 10;
	}
	return (res);
}

char	*ft_itoa_hex(unsigned int n, int base)
{
	char		*res;
	int			i;

	i = allocation((int)n, &res, base);
	if (res == NULL)
		return (NULL);
	res[i--] = '\0';
	if (n == 0)
		res[i] = '0';
	while (n > 0)
	{
		res[i--] = (n % base) + '0';
		n /= base;
	}
	return (res);
}
