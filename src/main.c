/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:32:26 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/29 09:20:29 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	delete_textures(t_cub3d *data)
{
	int	i;

	if (data->mlx_data.no)
		mlx_delete_texture(data->mlx_data.no);
	if (data->mlx_data.so)
		mlx_delete_texture(data->mlx_data.so);
	if (data->mlx_data.we)
		mlx_delete_texture(data->mlx_data.we);
	if (data->mlx_data.ea)
		mlx_delete_texture(data->mlx_data.ea);
	if (data->mlx_data.door[0])
		mlx_delete_texture(data->mlx_data.door[0]);
	i = 0;
	while (i < data->moon.frame_count)
	{
		if (data->moon.f[i])
			mlx_delete_texture(data->moon.f[i]);
		i++;
	}
}

void	save_textures(t_cub3d *data)
{
	data->mlx_data.no = mlx_load_png(data->bearings.no);
	data->mlx_data.so = mlx_load_png(data->bearings.so);
	data->mlx_data.we = mlx_load_png(data->bearings.we);
	data->mlx_data.ea = mlx_load_png(data->bearings.ea);
	data->moon.f[0] = mlx_load_png("./textures/moon/moon_frame_00.png");
	data->moon.f[1] = mlx_load_png("./textures/moon/moon_frame_01.png");
	data->moon.f[2] = mlx_load_png("./textures/moon/moon_frame_02.png");
	data->moon.f[3] = mlx_load_png("./textures/moon/moon_frame_03.png");
	data->mlx_data.door[0] = mlx_load_png("./textures/door.png");
	data->moon.frame = 0;
	data->moon.x = 500;
	data->moon.y = 0;
	data->moon.frame_count = 4;
	if (!data->mlx_data.no || !data->mlx_data.so
		|| !data->mlx_data.we || !data->mlx_data.ea
		|| !data->moon.f[0] || !data->moon.f[1]
		|| !data->moon.f[2] || !data->moon.f[3]
		|| !data->mlx_data.door[0])
	{
		delete_textures(data);
		free_and_exit(data, "Error\nFaild to load map\n");
	}
}

int	main(int argc, char *argv[])
{
	t_cub3d	data;

	if (argc != 2 || !argv[1][0])
	{
		ft_putstr_fd("Error\n./cub3d file_name.cup\n", 2);
		return (1);
	}
	check_file_name(argv[1]);
	check_empty_read(argv[1]);
	data.file.all_file = read_map(argv[1]);
	parse_map(&data);
	save_textures(&data);
	handle_drawing(&data.mlx_data, &data);
	free_and_exit(&data, NULL);
	return (0);
}
