/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:06:10 by aatieh            #+#    #+#             */
/*   Updated: 2025/01/07 19:52:14 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../inc/libft.h"

char	*check_status(char **cmd, char **paths, char *path)
{
	if (access(path, X_OK) == 0)
		return (path);
	if (access(path, F_OK) == 0)
	{
		ft_dprintf(2, "pipex: %s: Permission denied\n", cmd[0]);
		if (cmd[0] != path)
			free(path);
		free_all(NULL, paths);
		free_all(NULL, cmd);
		exit(126);
	}
	return (path);
}

char	**get_all_paths(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*get_final_path(char **paths, char *tmp, char **cmd)
{
	char	*path;
	char	**tmp_path;

	if (!paths || !tmp)
		return (NULL);
	tmp_path = paths;
	path = NULL;
	while (tmp_path && tmp_path[0])
	{
		path = ft_strjoin(*tmp_path, tmp);
		if (!path)
			break ;
		if (access(path, F_OK) == 0)
			return (check_status(cmd, paths, path));
		free(path);
		path = NULL;
		tmp_path++;
	}
	return (path);
}

char	*get_path(char **cmd, char **envp, int fd[2])
{
	char	**paths;
	char	*path;
	char	*tmp;

	if (access(cmd[0], F_OK) == 0)
		return (ft_strdup(check_status(cmd, NULL, cmd[0])));
	tmp = ft_strjoin("/", cmd[0]);
	paths = get_all_paths(envp);
	if (!paths || !tmp)
	{
		free_all(tmp, cmd);
		return (NULL);
	}
	path = get_final_path(paths, tmp, cmd);
	free_all(tmp, paths);
	if (path == NULL)
	{
		ft_dprintf(2, "pipex: %s: command not found\n", cmd[0]);
		close_all(fd[0], fd[1]);
		free_all(NULL, cmd);
		exit(127);
	}
	return (path);
}
