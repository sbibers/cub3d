/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:25:08 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/23 13:32:43 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_zoomed_sprite(t_cub3d *data, mlx_texture_t *texture,
	t_sprite *sprite, t_texture_draw td)
{
	while (td.x < texture->width)
	{
		td.pixel_index = (td.y * texture->width + td.x) * 4;
		td.cr.r = texture->pixels[td.pixel_index + 0];
		td.cr.g = texture->pixels[td.pixel_index + 1];
		td.cr.b = texture->pixels[td.pixel_index + 2];
		td.cr.a = texture->pixels[td.pixel_index + 3];
		td.cr.color = ft_pixel(td.cr.r, td.cr.g, td.cr.b, td.cr.a);
		td.dy = 0;
		while (td.dy < td.zoom_h)
		{
			td.dx = 0;
			while (td.dx < td.zoom_w)
			{
				if (td.cr.a != 0)
					my_put_pixel(data->mlx_data.img, td.x * td.zoom_w + td.dx
						+ sprite->x, td.y * td.zoom_h + td.dy + sprite->y,
						td.cr.color);
				td.dx++;
			}
			td.dy++;
		}
		td.x++;
	}
}

int	out_of_frame(t_cub3d *data, t_sprite *sprite)
{
	float	x_1;
	float	x_2;
	float	angle;

	if (sin(data->player.angle) > 0)
		return (1);
	angle = data->player.angle - PI / FOV;
	x_1 = data->player.x / BLOCK - (data->player.y / BLOCK) / tan(angle);
	if (sin(angle) > 0 && cos(angle) > 0)
		x_1 = data->map.width;
	else if (sin(angle) > 0 && cos(angle) < 0)
		x_1 = 0;
	angle = data->player.angle + PI / FOV;
	x_2 = data->player.x / BLOCK - (data->player.y / BLOCK) / tan(angle);
	if (sin(angle) > 0 && cos(angle) < 0)
		x_2 = 0;
	else if ((sin(angle) > 0 && cos(angle) > 0) || x_2 > data->map.width)
		x_2 = data->map.width;
	if (x_2 < data->map.width * 0.5)
		return (1);
	sprite->x = ((data->map.width * 0.5 - x_1) / (x_2 - x_1)) * CUB_WIDTH;
	return (0);
}

void	draw_sprite(t_cub3d *data, mlx_texture_t *texture, t_sprite *sprite)
{
	t_texture_draw	td;

	td.y = 0;
	if (out_of_frame(data, sprite))
		return ;
	td.zoom_h = 0.5;
	td.zoom_w = 0.5;
	while (td.y < texture->height)
	{
		td.x = 0;
		draw_zoomed_sprite(data, texture, sprite, td);
		td.y++;
	}
}
