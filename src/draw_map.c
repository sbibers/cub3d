/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:19:52 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/28 16:00:58 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_cube(float xy[2], int size, int color, t_mlx_cube3d *mlx_data)
{
	int	i;

	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, xy[0] + i++, xy[1], color);
	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, xy[0], xy[1] + i++, color);
	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, xy[0] + size, xy[1] + i++, color);
	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, xy[0] + i++, xy[1] + size, color);
}

void	draw_player(t_cub3d *data, t_player *player)
{
	float	player_pos_x;
	float	player_pos_y;
	float	real_x;
	float	real_y;

	real_x = player->x / BLOCK;
	real_y = player->y / BLOCK;
	if (real_x < MINI_SIZE + 0.5)
		player_pos_x = ((MINI_SIZE + real_x - floor(real_x)) * data->scale)
			- ((MINI_SIZE - floor(real_x)) * data->scale);
	else
		player_pos_x = (MINI_SIZE + 0.5) * data->scale;
	if (real_y < MINI_SIZE + 0.5)
		player_pos_y = ((MINI_SIZE + real_y - floor(real_y)) * data->scale)
			- ((MINI_SIZE - floor(real_y)) * data->scale);
	else
		player_pos_y = (MINI_SIZE + 0.5) * data->scale;
	draw_cube((float []){player_pos_x + 2, player_pos_y + 2},
		1, 0xFF0000FF, &data->mlx_data);
}

void	draw_map_loop(t_map *map, t_mlx_cube3d *mlx_data,
			t_cub3d *data, t_draw_map *var)
{
	var->j = var->player_x - MINI_SIZE;
	if (var->j < 0)
		var->j = 0;
	var->ini_j = var->j;
	while (var->j < map->width && (var->j <= var->player_x
			+ MINI_SIZE || var->j <= var->ini_j + (MINI_SIZE * 2)))
	{
		if (map->map[var->i][var->j] == '1')
			draw_cube((float []){(var->j - var->ini_j) * data->scale + 2,
				(var->i - var->ini_i) * data->scale + 2},
				data->scale, 0x0000FFFF, mlx_data);
		else if ((map->map[var->i][var->j] == 'D'
			|| map->map[var->i][var->j] == 'O'))
			draw_cube((float []){(var->j - var->ini_j) * data->scale + 2,
				(var->i - var->ini_i) * data->scale + 2},
				data->scale, 0x0FF0FFFF, mlx_data);
		var->j++;
	}
}

void	draw_map(t_map *map, t_mlx_cube3d *mlx_data, t_cub3d *data)
{
	t_draw_map	var;

	ft_map_background(0, 0x000000FF, mlx_data->img);
	var.player_x = data->player.x / BLOCK;
	var.player_y = data->player.y / BLOCK;
	var.i = var.player_y - MINI_SIZE;
	if (var.i < 0)
		var.i = 0;
	var.ini_i = var.i;
	while (var.i < map->height && (var.i <= var.player_y + MINI_SIZE
			|| var.i <= var.ini_i + (MINI_SIZE * 2)))
	{
		draw_map_loop(map, mlx_data, data, &var);
		var.i++;
	}
	draw_cube((float []){0, 0},
		(BLOCK) * (MINI_SIZE + 0.7) * 0.5, 0xFFFFFFFF, mlx_data);
	draw_cube((float []){1, 1},
		(BLOCK) * (MINI_SIZE + 0.7) * 0.5, 0xFFFFFFFF, mlx_data);
	draw_player(data, &data->player);
}

void	handle_drawing(t_mlx_cube3d *mlx_data, t_cub3d *data)
{
	mlx_data->mlx = mlx_init(CUB_WIDTH, CUB_HEIGHT, "game", false);
	if (!mlx_data->mlx)
	{
		delete_textures(data);
		free_and_exit(data, "Error\nFailed to initialize mlx\n");
	}
	mlx_data->img = mlx_new_image(mlx_data->mlx, CUB_WIDTH, CUB_HEIGHT);
	if (!mlx_data->img)
	{
		delete_textures(data);
		mlx_terminate(mlx_data->mlx);
		free_and_exit(data, "Error\nFailed to create image\n");
	}
	determine_init_angle(data);
	data->player.x_delta = 0;
	mlx_image_to_window(mlx_data->mlx, mlx_data->img, 0, 0);
	mlx_key_hook(mlx_data->mlx, ft_open_door, data);
	mlx_cursor_hook(mlx_data->mlx, mouse_handler, data);
	mlx_loop_hook(mlx_data->mlx, ft_draw_loop, data);
	mlx_loop(mlx_data->mlx);
	free_mlx_data(data);
}
