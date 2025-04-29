/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:22:37 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/22 19:06:10 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	touch(t_player *player, float step_x, float step_y, t_cub3d *data)
{
	int	x;
	int	y;

	x = (player->x + step_x) / BLOCK;
	y = (player->y + step_y) / BLOCK;
	if (y >= data->map.height || x >= data->map.width
		|| data->map.map[y] == NULL
		|| data->map.map[y][x] == '\0'
		|| data->map.map[y][x] == '1'
		|| data->map.map[y][x] == 'D')
		return (true);
	return (false);
}

void	calculate_step(t_ray *ray, t_cub3d *data)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = ((data->player.x / BLOCK) - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - (data->player.x / BLOCK))
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = ((data->player.y / BLOCK) - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - (data->player.y / BLOCK))
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_cub3d *data)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0
			|| ray->map_y >= data->map.height
			|| ray->map_x >= data->map.width
			|| data->map.map[ray->map_y] == NULL
			|| data->map.map[ray->map_y][ray->map_x] == '\0'
			|| data->map.map[ray->map_y][ray->map_x] == '1'
			|| data->map.map[ray->map_y][ray->map_x] == 'D'
			|| data->map.map[ray->map_y][ray->map_x] == 'O')
			break ;
	}
}

mlx_texture_t	*get_texture(t_ray *ray, t_cub3d *data)
{
	if (data->map.map[ray->map_y][ray->map_x] == 'D'
		|| data->map.map[ray->map_y][ray->map_x] == 'O')
		return (data->mlx_data.door[0]);
	else if (ray->side == 0 && ray->ray_dir_x > 0)
		return (data->mlx_data.so);
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		return (data->mlx_data.no);
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		return (data->mlx_data.ea);
	else
		return (data->mlx_data.we);
}

void	draw_ray_line(t_cub3d *data, float ray_angle, int x)
{
	t_ray	ray;

	ray.map_x = (int)data->player.x / BLOCK;
	ray.map_y = (int)data->player.y / BLOCK;
	ray.ray_dir_x = cos(ray_angle);
	ray.ray_dir_y = sin(ray_angle);
	ray.angle = ray_angle;
	if (ray.ray_dir_x == 0)
		ray.delta_dist_x = 1e30;
	else
		ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
	if (ray.ray_dir_y == 0)
		ray.delta_dist_y = 1e30;
	else
		ray.delta_dist_y = fabs(1 / ray.ray_dir_y);
	calculate_step(&ray, data);
	perform_dda(&ray, data);
	draw_vertical_line(&ray, data, x);
}
