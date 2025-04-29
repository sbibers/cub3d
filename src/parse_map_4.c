/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:13:49 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/22 18:38:52 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	parse_color_line(t_cub3d *data, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (data->floor_color)
			free(data->floor_color);
		data->floor_color = ft_strndup(line + 2, ft_strlen(line) - 2);
		if (!data->floor_color)
			free_and_exit(data, "Error\nFaild to allocate\n");
		data->counter.count_floor_color++;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (data->ceiling_color)
			free(data->ceiling_color);
		data->ceiling_color = ft_strndup(line + 2, ft_strlen(line) - 2);
		if (!data->ceiling_color)
			free_and_exit(data, "Error\nFaild to allocate\n");
		data->counter.count_ceiling_color++;
	}
}

static void	parse_texture_line_2(t_cub3d *data, char *line)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (data->bearings.we)
			free(data->bearings.we);
		data->bearings.we = ft_strndup(line + 3, ft_strlen(line) - 3);
		if (!data->bearings.we)
			free_and_exit(data, "Error\nFaild to allocate\n");
		data->counter.count_we++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (data->bearings.ea)
			free(data->bearings.ea);
		data->bearings.ea = ft_strndup(line + 3, ft_strlen(line) - 3);
		if (!data->bearings.ea)
			free_and_exit(data, "Error\nFaild to allocate\n");
		data->counter.count_ea++;
	}
}

static void	parse_texture_line(t_cub3d *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (data->bearings.no)
			free(data->bearings.no);
		data->bearings.no = ft_strndup(line + 3, ft_strlen(line) - 3);
		if (!data->bearings.no)
			free_and_exit(data, "Error\nFaild to allocate\n");
		data->counter.count_no++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (data->bearings.so)
			free(data->bearings.so);
		data->bearings.so = ft_strndup(line + 3, ft_strlen(line) - 3);
		if (!data->bearings.so)
			free_and_exit(data, "Error\nFaild to allocate\n");
		data->counter.count_so++;
	}
	else
		parse_texture_line_2(data, line);
}

static void	parse_other_lines(t_cub3d *data, char *line)
{
	data->file.complete_file = ft_strjoin_gnl(data->file.complete_file, line);
	if (!data->file.complete_file)
		free_and_exit(data, "Error\nFaild to allocate\n");
}

void	split_lines(t_cub3d *data)
{
	int	i;

	i = -1;
	init_data(data);
	while (data->file.split_all_file[++i])
	{
		if (ft_strncmp(data->file.split_all_file[i], "F ", 2) == 0
			|| ft_strncmp(data->file.split_all_file[i], "C ", 2) == 0)
			parse_color_line(data, data->file.split_all_file[i]);
		else if (ft_strncmp(data->file.split_all_file[i], "NO ", 3) == 0
			|| ft_strncmp(data->file.split_all_file[i], "SO ", 3) == 0
			|| ft_strncmp(data->file.split_all_file[i], "WE ", 3) == 0
			|| ft_strncmp(data->file.split_all_file[i], "EA ", 3) == 0)
			parse_texture_line(data, data->file.split_all_file[i]);
		else
			parse_other_lines(data, data->file.split_all_file[i]);
	}
	if (!data->floor_color || !data->ceiling_color || !data->bearings.ea
		|| !data->bearings.no || !data->bearings.so || !data->bearings.we
		|| data->counter.count_ceiling_color != 1
		|| data->counter.count_floor_color != 1 || data->counter.count_ea != 1
		|| data->counter.count_so != 1 || data->counter.count_we != 1
		|| data->counter.count_no != 1)
		free_and_exit(data, "Error\nFile must have1of this:WE,SO,NO,EA,C,F\n");
	check_bearings_colors(data);
}
