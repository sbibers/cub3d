/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:05:48 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/15 21:07:20 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	exit_allocation(char **split, t_cub3d *data)
{
	ft_free_split(split);
	free(data->file.all_file);
	ft_putstr_fd("Error\nAllocation failed\n", 2);
	exit(1);
}

void	creat_2darray_2(int i, int count, char **split, t_cub3d *data)
{
	int	start;

	while (data->file.all_file[i])
	{
		start = i;
		while (data->file.all_file[i] && data->file.all_file[i] != '\n')
			i++;
		if (i > start)
		{
			split[count] = ft_strndup(data->file.all_file + start, i - start);
			if (!split[count])
				exit_allocation(split, data);
		}
		else
		{
			split[count] = ft_strdup("\n");
			if (!split[count])
				exit_allocation(split, data);
		}
		count++;
		if (data->file.all_file[i] == '\n')
			i++;
	}
	split[count] = NULL;
}

char	**create_2darray(t_cub3d *data)
{
	int		i;
	int		count;
	char	**split;

	i = 0;
	count = 0;
	while (data->file.all_file[i])
	{
		count++;
		while (data->file.all_file[i] && data->file.all_file[i] != '\n')
			i++;
		if (data->file.all_file[i] == '\n')
			i++;
	}
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
	{
		free(data->file.all_file);
		ft_putstr_fd("Error\nAllocation failed\n", 2);
		exit(1);
	}
	creat_2darray_2(0, 0, split, data);
	return (split);
}
