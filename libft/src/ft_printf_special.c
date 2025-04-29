/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_special.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:23:28 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/25 21:08:49 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/ft_printf.h"

int	print_main_nbr(char *string, va_list args, int i, t_printf *res)
{
	int				m;
	int				n;
	unsigned int	nbr;

	m = 0;
	if (string[i] == 'd' || string[i] == 'i')
	{
		n = va_arg(args, int);
		res->len = nbr_alloc(n, res, 0, 10);
		ft_putnbr_print(n, res, &m);
	}
	else if (string[i] == 'u')
	{
		nbr = va_arg(args, unsigned int);
		res->len = nbr_alloc(nbr, res, 0, 10);
		ft_putnbr_print(nbr, res, &m);
	}
	return (res->len);
}

int	print_main_hex(char *string, va_list args, int i, t_printf *res)
{
	unsigned long	nbr;
	int				m;

	m = 0;
	if (string[i] == 'p')
	{
		nbr = (size_t)va_arg(args, void *);
		res->str = malloc(sizeof(char) * 19);
		ft_putnbr_hex_print(nbr, res, 3, &m);
		res->len = ft_strlen(res->str);
	}
	else if (string[i] == 'x')
	{
		nbr = va_arg(args, unsigned int);
		res->len = nbr_alloc(nbr, res, 1, 16);
		ft_putnbr_hex_print(nbr, res, 1, &m);
	}
	else if (string[i] == 'X')
	{
		nbr = va_arg(args, unsigned int);
		res->len = nbr_alloc(nbr, res, 2, 16);
		ft_putnbr_hex_print(nbr, res, 2, &m);
	}
	return (res->len);
}

int	print_main(char *string, va_list args, int i, t_printf *res)
{
	char			c;

	res->len = 0;
	res->str = NULL;
	if (string[i] == 'c')
	{
		c = va_arg(args, int);
		res->len = 1;
		res->str = ft_strdup(&c);
	}
	else if (string[i] == 's')
	{
		res->str = ft_strdup(empty_check(va_arg(args, char *)));
		res->len = ft_strlen(res->str);
	}
	else if (string[i] == 'd' || string[i] == 'i' || string[i] == 'u')
		res->len = print_main_nbr(string, args, i, res);
	else if (string[i] == 'p' || string[i] == 'x' || string[i] == 'X')
		res->len = print_main_hex(string, args, i, res);
	else
	{
		res->len = 1;
		res->str = ft_strdup("%");
	}
	return (res->len);
}
