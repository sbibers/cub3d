/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:27:32 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/27 11:25:48 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mouse_handler(double xdelta, double ydelta, void *param)
{
	t_cub3d		*data;
	t_player	*player;

	data = (t_cub3d *)param;
	player = &data->player;
	(void)ydelta;
	if (xdelta < player->x_delta)
		data->player.angle -= ROTATE_SPEED / 1.5;
	else if (xdelta > player->x_delta)
		data->player.angle += ROTATE_SPEED / 1.5;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	else if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	player->x_delta = xdelta;
}

void	determine_init_angle(t_cub3d *data)
{
	if (data->player.c == 'N')
		data->player.angle = 270 * (PI / 180);
	else if (data->player.c == 'S')
		data->player.angle = 90 * (PI / 180);
	else if (data->player.c == 'W')
		data->player.angle = 180 * (PI / 180);
	else if (data->player.c == 'E')
		data->player.angle = 0 * (PI / 180);
	data->player.fraction = PI / (FOV * 0.5) / CUB_WIDTH;
	data->scale = BLOCK / MINI_SCALE;
}

void	move_player_extend(t_cub3d *data, t_move_player mv)
{
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_A)
		&& !touch(&data->player, mv.step1_y, -mv.step1_x, data)
		&& !touch(&data->player, mv.step2_y, -mv.step2_x, data))
	{
		data->player.x += SPEED * sin(data->player.angle);
		data->player.y -= SPEED * cos(data->player.angle);
	}
	else if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_D)
		&& !touch(&data->player, -mv.step1_y, mv.step1_x, data)
		&& !touch(&data->player, -mv.step2_y, mv.step2_x, data))
	{
		data->player.x -= SPEED * sin(data->player.angle);
		data->player.y += SPEED * cos(data->player.angle);
	}
}

void	move_player(t_cub3d *data)
{
	t_move_player	mv;

	mv.step1_x = COLISION * cos(data->player.angle + PI / 12);
	mv.step1_y = COLISION * sin(data->player.angle + PI / 12);
	mv.step2_x = COLISION * cos(data->player.angle - PI / 12);
	mv.step2_y = COLISION * sin(data->player.angle - PI / 12);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_W)
		&& !touch(&data->player, mv.step1_x, mv.step1_y, data)
		&& !touch(&data->player, mv.step2_x, mv.step2_y, data))
	{
		data->player.x += SPEED * cos(data->player.angle);
		data->player.y += SPEED * sin(data->player.angle);
	}
	else if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_S)
		&& !touch(&data->player, -mv.step1_x, -mv.step1_y, data)
		&& !touch(&data->player, -mv.step2_x, -mv.step2_y, data))
	{
		data->player.x -= SPEED * cos(data->player.angle);
		data->player.y -= SPEED * sin(data->player.angle);
	}
	else
		move_player_extend(data, mv);
}

void	rotate_player(t_cub3d *data)
{
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx_data.mlx);
	else if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_LEFT))
		data->player.angle -= ROTATE_SPEED;
	else if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_RIGHT))
		data->player.angle += ROTATE_SPEED;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	else if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
}
