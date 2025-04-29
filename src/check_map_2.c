/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:04:54 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/22 18:31:02 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	pad_map_2(t_cub3d *data, int len, int max_len, int y)
{
	char	*new_line;

	new_line = malloc(max_len + 1);
	if (!new_line)
	{
		ft_free_split(data->map.copy_map);
		free_and_exit(data, "Error\nFaild to allocate\n");
	}
	ft_memcpy(new_line, data->map.copy_map[y], len);
	ft_memset(new_line + len, ' ', max_len - len);
	new_line[max_len] = '\0';
	free(data->map.copy_map[y]);
	data->map.copy_map[y] = new_line;
}

void	pad_map(t_cub3d *data)
{
	int	y;
	int	len;
	int	max_len;

	y = 0;
	max_len = 0;
	while (data->map.copy_map[y])
	{
		len = ft_strlen(data->map.copy_map[y]);
		if (len > max_len)
			max_len = len;
		y++;
	}
	data->map.width = max_len;
	data->map.height = y;
	y = 0;
	while (data->map.copy_map[y])
	{
		len = ft_strlen(data->map.copy_map[y]);
		if (len < max_len)
			pad_map_2(data, len, max_len, y);
		y++;
	}
}

static void	stop_check_map_borders(t_cub3d *data)
{
	ft_free_split(data->map.copy_map);
	free_and_exit(data, "Error\nWrong map\n");
}

static void	check_map_borders_2(t_cub3d *data, int y)
{
	int	last_char;

	if (data->map.copy_map[y][0] != '1' && data->map.copy_map[y][0] != ' '
		&& data->map.copy_map[y][0] != '\t')
		stop_check_map_borders(data);
	last_char = ft_strlen(data->map.copy_map[y]) - 1;
	if (last_char >= 0
		&& data->map.copy_map[y][last_char] != '1'
		&& data->map.copy_map[y][last_char] != ' '
		&& data->map.copy_map[y][last_char] != '\t')
		stop_check_map_borders(data);
}

void	check_map_borders(t_cub3d *data)
{
	int	y;
	int	x;
	int	last_row;

	x = -1;
	while (data->map.copy_map[0][++x])
	{
		if (data->map.copy_map[0][x] != '1'
			&& data->map.copy_map[0][x] != ' '
			&& data->map.copy_map[0][x] != '\t')
			stop_check_map_borders(data);
	}
	x = -1;
	last_row = data->map.height - 1;
	while (data->map.copy_map[last_row][++x])
	{
		if (data->map.copy_map[last_row][x] != '1'
			&& data->map.copy_map[last_row][x] != ' '
			&& data->map.copy_map[last_row][x] != '\t')
			stop_check_map_borders(data);
	}
	y = -1;
	while (data->map.copy_map[++y])
		check_map_borders_2(data, y);
}
