/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:03 by aatieh            #+#    #+#             */
/*   Updated: 2025/02/10 14:39:21 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"
#include "../inc/libft.h"

char	*merge(char *word1, char *word2, int f, int i)
{
	char	*res;
	int		j;

	j = 0;
	if (f == 0)
		res = malloc(sizeof(char) * (ft_strlen(word1)
					+ ft_strlen(word2) + 1));
	else
		res = malloc(sizeof(char) * (ft_strlen(word1) + f + 2));
	if (!res)
		free(word1);
	while (word1 && word1[i])
	{
		res[i] = word1[i];
		i++;
	}
	while (word1 && ((f == 0 && word2[j]) || (j < f)))
	{
		res[i + j] = word2[j];
		j++;
		res[i + j] = '\0';
	}
	if (word1)
		free(word1);
	return (res);
}

t_line_list	*find_buffer(int fd, t_line_list **storage, t_line_list *tmp)
{
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_line_list));
	if (!tmp)
		return (NULL);
	tmp->buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp->buff)
		free(tmp);
	if (!tmp)
		return (NULL);
	ft_bzero((tmp->buff), BUFFER_SIZE + 1);
	tmp->fd = fd;
	if (!*storage)
	{
		tmp->next = NULL;
		*storage = tmp;
		return (*storage);
	}
	tmp->next = *storage;
	*storage = tmp;
	return (tmp);
}

int	first_step(t_line_list **storage, int fd, int *bytes_read, char **res)
{
	int			i;
	char		*buff;
	t_line_list	*current;

	current = find_buffer(fd, storage, *storage);
	buff = current->buff;
	i = ft_strchr_find(buff, '\n');
	if (ft_strlen(buff))
		*res = merge (*res, buff, i, 0);
	if (!*res)
		return (-1);
	if (i != 0)
	{
		ft_memmove(buff, (buff + i), ft_strlen(buff + i - 1));
		return (i);
	}
	*bytes_read = read(fd, buff, BUFFER_SIZE);
	if (*bytes_read == -1)
		return (free (*res), -1);
	ft_bzero((buff + *bytes_read), BUFFER_SIZE - *bytes_read + 1);
	return (i);
}

char	*check_buffer(int fd, t_line_list *current, char *res,
			t_line_list **storage)
{
	char	*buff;
	int		i;
	int		bytes_read;

	i = 0;
	res[0] = '\0';
	buff = current->buff;
	bytes_read = BUFFER_SIZE;
	while (i == 0)
	{
		i = first_step(storage, fd, &bytes_read, &res);
		if (i == -1)
			return (NULL);
		if ((bytes_read == 0 && !ft_strlen(buff)))
		{
			if (!ft_strlen(res))
			{
				free (res);
				return (NULL);
			}
			return (res);
		}
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static t_line_list	*storage;
	char				*res;
	t_line_list			*current;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	res = malloc(sizeof(char));
	if (!res)
	{
		ft_lstclear_item(&storage, fd);
		return (NULL);
	}
	current = find_buffer(fd, &storage, storage);
	if (!current)
	{
		free(res);
		return (NULL);
	}
	res = check_buffer(fd, current, res, &storage);
	if (res == NULL || current->buff[0] == '\0')
		ft_lstclear_item(&storage, fd);
	return (res);
}
