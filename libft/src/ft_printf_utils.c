/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:28:41 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/25 21:08:49 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/ft_printf.h"

void	free_printf(t_printf *res)
{
	t_printf	*tmp;

	while (res)
	{
		tmp = res->next;
		if (res->str)
			free(res->str);
		free(res);
		res = tmp;
	}
}

int	write_printf(char *src, char *dest, int char_num)
{
	int	i;

	i = 0;
	while (src[i] && i < char_num)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (i);
}

int	write_char_printf(char c, char *dest)
{
	dest[0] = c;
	dest[1] = '\0';
	return (1);
}

char	*empty_check(char *string)
{
	if (!string)
		return ("(null)");
	return (string);
}

int	nbr_alloc(long long n, t_printf *res, int j, int base)
{
	int	i;

	i = 0;
	if (j == 3)
		i += 2;
	if (j == 3 && n == 0)
		i = 5;
	else if (n == 0)
		i++;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		i++;
		n /= base;
	}
	res->str = malloc(sizeof(char) * (i + 1));
	return (i);
}
