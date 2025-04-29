/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:15:44 by aatieh            #+#    #+#             */
/*   Updated: 2025/01/07 19:52:14 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../inc/libft.h"

void	free_all(char *str, char **split)
{
	int	i;

	if (str)
		free(str);
	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	close_all(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

int	wait_for_all(t_pipex *vars)
{
	int	last_status;
	int	pid;
	int	status;

	last_status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (pid == vars->last_id)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
	}
	return (last_status);
}

void	check_access(char *arg, t_pipex *vars, int is_first)
{
	if (is_first)
	{
		if (access(arg, R_OK) == -1)
		{
			if (access(arg, F_OK) == -1)
				ft_dprintf(2, "pipex: %s: No such file or directory\n", arg);
			else
				ft_dprintf(2, "pipex: %s: Permission denied\n", arg);
			close_all(vars->pipefd[0], vars->pipefd[1]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (access(arg, W_OK) == -1)
		{
			ft_dprintf(2, "pipex: %s: Permission denied\n", arg);
			close_all(vars->pipefd[0], vars->pipefd[1]);
			exit(EXIT_FAILURE);
		}
	}
}
