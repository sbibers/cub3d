/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:37:27 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/26 07:23:12 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/ft_printf.h"

int	ft_putnbr_fd(long n, int fd)
{
	int		i;
	char	r;

	i = 1;
	if (n < 0)
	{
		write (fd, "-", 1);
		n *= -1;
		i++;
	}
	if (n > 9)
		i += ft_putnbr_fd(n / 10, fd);
	r = (n % 10) + '0';
	write (fd, &r, 1);
	return (i);
}

int	ft_putnbr_print(long n, t_printf *res, int *i)
{
	char	r;

	if (!res->str)
		return (0);
	if (n < 0)
	{
		*i += write_char_printf('-', res->str);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_print(n / 10, res, i);
	r = (n % 10) + '0';
	*i += write_char_printf(r, res->str + *i);
	return (*i + 1);
}
