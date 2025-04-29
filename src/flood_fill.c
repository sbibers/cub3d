/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:24:52 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/23 11:20:03 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_poisition_of_player(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S'
				|| data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
			{
				data->player.c = data->map.map[i][j];
				data->player.y = (i + 0.5) * BLOCK;
				data->player.x = (j + 0.5) * BLOCK;
			}
			j++;
		}
		i++;
	}
}

void	heigh_width(t_cub3d *data)
{
	int	i;

	i = 0;
	data->map.height = 0;
	data->map.width = 0;
	while (data->map.map[i])
	{
		if ((int)ft_strlen(data->map.map[i]) > data->map.width)
			data->map.width = ft_strlen(data->map.map[i]);
		i++;
		data->map.height++;
	}
}

void	flood_fill_2(t_cub3d *data, int y, int x)
{
	if (y < 0 || x < 0 || y >= data->map.height || x >= data->map.width)
	{
		ft_free_split(data->map.copy_map);
		free_and_exit(data, "Error\nMap must be surrounded\n");
	}
	if (data->map.copy_map[y][x] == '1' || data->map.copy_map[y][x] == '2')
		return ;
	data->map.copy_map[y][x] = '2';
	flood_fill_2(data, y + 1, x);
	flood_fill_2(data, y - 1, x);
	flood_fill_2(data, y, x + 1);
	flood_fill_2(data, y, x - 1);
}

void	flood_fill(t_cub3d *data, int player_y, int player_x)
{
	int	i;
	int	j;

	flood_fill_2(data, player_y, player_x);
	i = 0;
	while (data->map.copy_map[i])
	{
		j = 0;
		while (data->map.copy_map[i][j])
		{
			if (data->map.copy_map[i][j] == '0')
				flood_fill_2(data, i, j);
			j++;
		}
		i++;
	}
}
