/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:59:10 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/25 04:16:03 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_printf
{
	char			*str;
	int				len;
	struct s_printf	*next;
}					t_printf;

char		*ft_strjoin_printf(t_printf *og_res, int count);

int			print_main(char *string, va_list args, int i, t_printf *res);
int			print_main_hex(char *string, va_list args, int i, t_printf *res);
int			print_main_nbr(char *string, va_list args, int i, t_printf *res);
t_printf	*ft_printf_helper(char *string, va_list *args, int *count);

int			write_printf(char *src, char *dest, int char_num);
int			write_char_printf(char c, char *dest);
char		*empty_check(char *string);
void		free_printf(t_printf *res);
int			nbr_alloc(long long n, t_printf *res, int j, int base);

int			print_string(char *string, t_printf *res, int *i);
int			ft_putnbr_print(long n, t_printf *res, int *i);
int			ft_putnbr_hex_print(unsigned long n, t_printf *res, int j, int *i);

int			ft_printf(const char *string, ...);
int			ft_dprintf(int fd, const char *string, ...);

#endif
