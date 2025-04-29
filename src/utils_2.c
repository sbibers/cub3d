/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:16:00 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/28 16:00:23 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_open_door(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*data;
	int		next_x;
	int		next_y;

	data = (t_cub3d *)param;
	next_x = data->player.x + COLISION * 1.5 * cos(data->player.angle);
	next_y = data->player.y + COLISION * 1.5 * sin(data->player.angle);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
	{
		if (data->map.map[next_y / BLOCK][next_x / BLOCK] == 'D')
			data->map.map[next_y / BLOCK][next_x / BLOCK] = 'O';
		else if (data->map.map[next_y / BLOCK][next_x / BLOCK] == 'O')
			data->map.map[next_y / BLOCK][next_x / BLOCK] = 'D';
	}
}

char	**ft_dup_matrix(char **m, int size, int flag)
{
	char	**str;
	int		i;
	int		n;

	n = ft_strlen_matrix(m);
	str = malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (m[i] && i < size)
	{
		str[i] = ft_strdup(m[i]);
		if (!str[i])
		{
			ft_free_split(str);
			return (NULL);
		}
		i++;
	}
	if (flag == 1)
		ft_free_split(m);
	str[i] = NULL;
	return (str);
}

void	init_data(t_cub3d *data)
{
	data->map.map = NULL;
	data->file.complete_file = NULL;
	data->floor_color = NULL;
	data->ceiling_color = NULL;
	data->bearings.ea = NULL;
	data->bearings.no = NULL;
	data->bearings.so = NULL;
	data->bearings.we = NULL;
	data->counter.count_ea = 0;
	data->counter.count_no = 0;
	data->counter.count_so = 0;
	data->counter.count_we = 0;
	data->counter.count_floor_color = 0;
	data->counter.count_ceiling_color = 0;
}

void	ft_map_background(uint32_t start, uint32_t color, mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	size;

	i = 0;
	size = (BLOCK) * (MINI_SIZE + 0.7) * 0.5;
	while (i < size)
	{
		j = 0;
		while (j < size)
			my_put_pixel(img, i, start + j++, color);
		i++;
	}
}
