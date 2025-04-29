/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:11:59 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/16 13:39:33 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	normalize_config_line_2(t_data_normalize *data)
{
	data->tmp_key = data->key;
	data->tmp_value = data->value;
	data->key = ft_strtrim(data->tmp_key, " \t");
	data->value = ft_strtrim(data->tmp_value, " \t");
	free(data->tmp_key);
	free(data->tmp_value);
	if (!data->key || !data->value)
	{
		free(data->key);
		free(data->value);
		return (0);
	}
	data->joined = ft_strjoin(data->key, " ");
	free(data->key);
	if (!data->joined)
	{
		free(data->value);
		return (0);
	}
	data->final = ft_strjoin_gnl(data->joined, data->value);
	free(data->value);
	return (1);
}

static char	*normalize_config_line(const char *line)
{
	t_data_normalize	data;
	int					i;
	int					start;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	data.key = ft_substr(line, start, i - start);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	data.value = ft_strdup(line + i);
	if (!data.key || !data.value)
	{
		free(data.key);
		free(data.value);
		return (NULL);
	}
	if (!normalize_config_line_2(&data))
		return (NULL);
	return (data.final);
}

static int	check_string(char *check)
{
	if ((ft_strncmp(check, "NO", 2) == 0 || ft_strncmp(check, "SO", 2) == 0
			|| ft_strncmp(check, "WE", 2) == 0 || ft_strncmp(check, "EA",
				2) == 0 || ft_strncmp(check, "F", 1) == 0 || ft_strncmp(check,
				"C", 1) == 0) || (ft_strncmp(check, "1", 1) != 0
			&& ft_strncmp(check, "0", 1) != 0))
		return (1);
	return (0);
}

static void	trim_config_2(char **lines, int flag)
{
	ft_free_split(lines);
	if (flag == 1)
		ft_putstr_fd("Error\nFailed to allocate split lines\n", 2);
	else
		ft_putstr_fd("Error\nnormalize failed\n", 2);
	exit(1);
}

void	trim_config_lines(char **lines)
{
	int		i;
	char	*check;
	char	*normalized;

	i = -1;
	while (lines[++i])
	{
		check = ft_strtrim(lines[i], " \t\n");
		if (!check)
			trim_config_2(lines, 1);
		if (check_string(check))
		{
			free(check);
			normalized = normalize_config_line(lines[i]);
			if (!normalized)
				trim_config_2(lines, 0);
			free(lines[i]);
			lines[i] = normalized;
		}
		else
			free(check);
	}
}
