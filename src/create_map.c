/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:21:13 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/22 18:33:37 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	create_map_2(t_cub3d *data, int *i, int *j)
{
	while (data->file.split_all_file[*i])
	{
		data->map.map[*j] = ft_strdup(data->file.split_all_file[*i]);
		if (!data->map.map[*j])
			free_and_exit(data, "Error\nFaild to allocate\n");
		(*i)++;
		(*j)++;
	}
	data->map.map[*j] = NULL;
	ft_free_split(data->file.split_all_file);
	data->file.split_all_file = NULL;
}

void	create_map(t_cub3d *data)
{
	int	i;
	int	j;
	int	map_lines;
	int	temp;

	i = 0;
	j = 0;
	map_lines = 0;
	while (data->file.split_all_file[i])
	{
		if (skip_spaces(data->file.split_all_file[i]))
			break ;
		i++;
	}
	temp = i;
	while (data->file.split_all_file[temp])
	{
		map_lines++;
		temp++;
	}
	data->map.map = malloc(sizeof(char *) * (map_lines + 1));
	if (!data->map.map)
		free_and_exit(data, "Error\nFaild to allocate\n");
	create_map_2(data, &i, &j);
}
