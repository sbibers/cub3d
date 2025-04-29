/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:57:00 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/25 21:08:49 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/ft_printf.h"

int	ft_putnbr_hex_fd(unsigned long n, int fd, int j)
{
	int	i;

	i = 1;
	if (j == 3 && n != 0)
	{
		write (1, "0x", 2);
		i += 2;
	}
	else if (j == 3 && n == 0)
		return (ft_putstr_fd("(nil)", fd));
	if (n > 15)
	{
		if (j == 2)
			i += ft_putnbr_hex_fd(n / 16, fd, 2);
		else
			i += ft_putnbr_hex_fd(n / 16, fd, 1);
	}
	if ((n % 16) < 10)
		ft_putchar_fd((n % 16) + '0', fd);
	else if (j == 2)
		ft_putchar_fd((n % 16) - 10 + 'A', fd);
	else
		ft_putchar_fd((n % 16) - 10 + 'a', fd);
	return (i);
}

int	ft_putnbr_hex_print(unsigned long n, t_printf *res, int j, int *i)
{
	if (!res->str)
		return (0);
	if (j == 3 && n != 0)
		*i += write_printf("0x", res->str, 2);
	else if (j == 3 && n == 0)
		return (write_printf("(nil)", res->str, 5));
	if (n > 15)
	{
		if (j == 2)
			ft_putnbr_hex_print(n / 16, res, 2, i);
		else
			ft_putnbr_hex_print(n / 16, res, 1, i);
	}
	if ((n % 16) < 10)
		*i += write_char_printf((n % 16) + '0', res->str + *i);
	else if (j == 2)
		*i += write_char_printf((n % 16) - 10 + 'A', res->str + *i);
	else
		*i += write_char_printf((n % 16) - 10 + 'a', res->str + *i);
	return (*i + 1);
}
