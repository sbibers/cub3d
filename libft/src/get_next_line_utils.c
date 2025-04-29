/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:10 by aatieh            #+#    #+#             */
/*   Updated: 2025/02/10 14:40:46 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"
#include "../inc/libft.h"

int	ft_strchr_find(const char *s, int c)
{
	int	i;

	i = 1;
	while (s[i - 1])
	{
		if (s[i - 1] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_lstclear_item(t_line_list **lst, int fd)
{
	t_line_list	*temp;
	t_line_list	*step;

	temp = *lst;
	while (temp)
	{
		if (temp->fd == fd)
			break ;
		step = temp;
		temp = temp->next;
	}
	if (!temp)
		return (NULL);
	if (temp->buff)
		free(temp->buff);
	if (temp == *lst)
		*lst = temp->next;
	else
		step->next = temp->next;
	if (temp)
		free(temp);
	return (NULL);
}
