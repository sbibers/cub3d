/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:10:05 by aatieh            #+#    #+#             */
/*   Updated: 2025/01/07 19:52:14 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../inc/libft.h"

static void	take_input(int tmp_fd, char *argv[])
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, argv[2], ft_strlen(argv[2]))
			&& ft_strlen(line) - 1 == ft_strlen(argv[2])
			&& line[ft_strlen(argv[2])] == '\n')
			break ;
		write(tmp_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
	close(tmp_fd);
}

static void	limiter_child(char *argv[], int pipefd[2], int tmp_fd, char **envp)
{
	char	**cmd;
	char	*path;

	close(pipefd[0]);
	path = NULL;
	cmd = ft_split(argv[3], ' ');
	if (cmd && cmd[0])
		path = get_path(cmd, envp, (int [2]){pipefd[1], tmp_fd});
	if (!path || tmp_fd == -1 || dup2(pipefd[1], STDOUT_FILENO) == -1
		|| dup2(tmp_fd, STDIN_FILENO) == -1)
	{
		free_all(path, cmd);
		close_all(tmp_fd, pipefd[1]);
		perror("here_doc");
		exit(2);
	}
	close_all(tmp_fd, pipefd[1]);
	execve(path, cmd, envp);
	ft_dprintf(2, "pipex : %s: Is a directory\n", cmd[0]);
	free_all(path, cmd);
	exit(126);
}

void	limiter_process(char *argv[], int argc, t_pipex *vars, char **envp)
{
	int	tmp_pipefd[2];

	if (pipe(tmp_pipefd) == -1)
	{
		perror("Pipe failed");
		close_all(vars->pipefd[0], vars->pipefd[1]);
		exit(1);
	}
	else
	{
		take_input(tmp_pipefd[1], argv);
		vars->children_num += 1;
		vars->last_id = fork();
		if (!vars->last_id)
			limiter_child(argv, vars->pipefd, tmp_pipefd[0], envp);
		else
		{
			if (vars->last_id == -1)
				ft_dprintf(2, "limiter fork failed\n");
			close_all(tmp_pipefd[0], vars->pipefd[1]);
		}
	}
	last_process(argv, argc, vars, envp);
}
