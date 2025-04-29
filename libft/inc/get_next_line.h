/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:18 by aatieh            #+#    #+#             */
/*   Updated: 2025/01/15 21:15:21 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_line_list
{
	int					fd;
	char				*buff;
	struct s_line_list	*next;
}	t_line_list;

char	*ft_lstclear_item(t_line_list **lst, int fd);

#endif
