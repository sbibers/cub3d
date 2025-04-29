/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:30:30 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/15 21:07:39 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

static void	handle_memory_allocation(char *str, int fd)
{
	if (str)
		free(str);
	close(fd);
	ft_putstr_fd("Error\nNULL check\n", 2);
	exit(1);
}

char	*read_map(char *map_name)
{
	char	*map;
	char	*str;
	int		fd;

	map = NULL;
	fd = open(map_name, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		map = ft_strjoin_gnl(map, str);
		if (!map)
			handle_memory_allocation(str, fd);
		free(str);
	}
	close(fd);
	return (map);
}
