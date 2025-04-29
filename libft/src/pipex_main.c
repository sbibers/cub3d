/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:45:11 by aatieh            #+#    #+#             */
/*   Updated: 2025/02/02 22:43:17 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../inc/libft.h"

int	child_process(char *arg, int in_fd, int out_fd, char **envp)
{
	char	**cmd;
	char	*path;

	path = NULL;
	cmd = ft_split(arg, ' ');
	if (cmd && cmd[0])
		path = get_path(cmd, envp, (int [2]){in_fd, out_fd});
	if (!cmd || in_fd == -1 || dup2(out_fd, STDOUT_FILENO) == -1
		|| dup2(in_fd, STDIN_FILENO) == -1 || !path)
	{
		free_all(path, cmd);
		close_all(in_fd, out_fd);
		ft_dprintf(2, "pipex: dup2 failed\n");
		exit(2);
	}
	close_all(in_fd, out_fd);
	execve(path, cmd, envp);
	ft_dprintf(2, "pipex : %s: Is a directory\n", cmd[0]);
	free_all(path, cmd);
	exit(126);
}

void	first_process(char *argv[], int argc, t_pipex *vars, char **envp)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	vars->children_num += 1;
	vars->last_id = fork();
	if (!vars->last_id)
	{
		check_access(argv[1], vars, 1);
		close(vars->pipefd[0]);
		child_process(argv[2], fd, vars->pipefd[1], envp);
	}
	else
	{
		close_all(fd, vars->pipefd[1]);
		if (vars->last_id == -1)
			ft_putstr_fd("first fork failed\n", 2);
		middle_process(argv, argc, vars, envp);
		last_process(argv, argc, vars, envp);
	}
}

void	middle_process(char *argv[], int argc, t_pipex *vars, char **envp)
{
	int	arg_num;
	int	tmp_pipefd;

	arg_num = 3;
	while (arg_num + 2 < argc)
	{
		tmp_pipefd = vars->pipefd[0];
		if (pipe(vars->pipefd) == -1)
		{
			perror("middle Pipe failed");
			return ;
		}
		vars->children_num += 1;
		vars->last_id = fork();
		if (!vars->last_id)
		{
			close(vars->pipefd[0]);
			child_process(argv[arg_num], tmp_pipefd, vars->pipefd[1], envp);
		}
		close_all(tmp_pipefd, vars->pipefd[1]);
		if (vars->last_id == -1)
			ft_putstr_fd("middle fork failed\n", 2);
		arg_num++;
	}
}

void	last_process(char *argv[], int argc, t_pipex *vars, char **envp)
{
	int	fd;

	if (ft_strncmp(argv[1], "here_doc", 10) != 0)
		fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	vars->children_num += 1;
	vars->last_id = fork();
	if (!vars->last_id)
	{
		check_access(argv[argc - 1], vars, 0);
		child_process(argv[argc - 2], vars->pipefd[0], fd, envp);
	}
	else
	{
		close_all(fd, vars->pipefd[0]);
		if (vars->last_id == -1)
			ft_putstr_fd("middle fork failed\n", 2);
	}
}

int	pipex(int argc, char *argv[], char **envp)
{
	t_pipex	vars;

	if (argc < 5)
	{
		ft_dprintf(2, "Not enough input\n");
		return (1);
	}
	if (ft_strncmp("here_doc", argv[1], 10) == 0 && argc != 6)
	{
		ft_dprintf(2, "Not enough input for here_doc\n");
		return (1);
	}
	if (pipe(vars.pipefd) == -1)
		return (perror("Pipe failed"), 3);
	vars.children_num = 0;
	if (ft_strncmp("here_doc", argv[1], 10) == 0)
		limiter_process(argv, argc, &vars, envp);
	else
		first_process(argv, argc, &vars, envp);
	return (wait_for_all(&vars));
}
