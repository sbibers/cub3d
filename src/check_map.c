/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:08 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/23 11:19:35 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_line_only_spaces(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	find_last_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (!is_line_only_spaces(map[i]))
			return (i);
		i--;
	}
	return (i);
}

static void	free_empty_last_lines(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map.map[i])
		i++;
	i--;
	while (i >= 0 && is_line_only_spaces(data->map.map[i]))
		i--;
	data->map.map = ft_dup_matrix(data->map.map, i + 1, 1);
	if (!data->map.map)
		free_and_exit(data, "Error\nFaild to allocate\n");
}

void	check_map_2(t_cub3d *data)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = find_last_line(data->map.map);
	while (data->map.map[i] && i <= size)
	{
		if (!skip_spaces(data->map.map[i]))
		{
			j = 0;
			while (data->map.map[i][j] && data->map.map[i][j] == ' ')
				j++;
			if (data->map.map[i][j] == '\n' || data->map.map[i][j] == '\0')
				free_and_exit(data, "Error\nWrong map\n");
		}
		i++;
	}
	free_empty_last_lines(data);
}

void	check_map(t_cub3d *data)
{
	int		i;
	int		j;
	int		player_count;
	char	c;

	i = -1;
	player_count = 0;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			c = data->map.map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			else if (c != '0' && c != '1' && c != ' ' && c != '\n' && c != 'D'
				&& c != '\t')
				free_and_exit(data, "Error\nWrong chars in map\n");
		}
	}
	if (player_count != 1)
		free_and_exit(data, "Error\nWrong number of players\n");
}
