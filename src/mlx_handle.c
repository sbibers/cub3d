/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:03:47 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/23 11:24:29 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_mlx_data(t_cub3d *data)
{
	delete_textures(data);
	mlx_delete_image(data->mlx_data.mlx, data->mlx_data.img);
	mlx_terminate(data->mlx_data.mlx);
}

void	ft_background(uint32_t start, uint32_t color, mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	height;

	i = 0;
	height = CUB_HEIGHT * 0.5;
	while (i < CUB_WIDTH)
	{
		j = 0;
		while (j < height)
			my_put_pixel(img, i, start + j++, color);
		i++;
	}
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	my_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if ((uint32_t)x >= img->width || (uint32_t)y >= img->height
		|| x < 0 || y < 0)
		return ;
	mlx_put_pixel(img, (uint32_t)x, (uint32_t)y, color);
}

void	ft_draw_loop(void *param)
{
	t_cub3d	*data;
	float	ray_angle;
	int		x;

	data = (t_cub3d *)param;
	ft_background(0, ft_pixel(data->top_color[0], data->top_color[1],
			data->top_color[2], 0xFF), data->mlx_data.img);
	draw_sprite(data, data->moon.f[(int)(0.01 * data->moon.frame++)
		% data->moon.frame_count], &data->moon);
	ft_background(CUB_HEIGHT * 0.5, ft_pixel(data->bott_color[0],
			data->bott_color[1], data->bott_color[2], 0xFF),
		data->mlx_data.img);
	rotate_player(data);
	move_player(data);
	ray_angle = data->player.angle - PI / FOV;
	x = 0;
	while (x < CUB_WIDTH)
	{
		draw_ray_line(data, ray_angle, x++);
		ray_angle += data->player.fraction;
	}
	draw_map(&data->map, &data->mlx_data, data);
}
