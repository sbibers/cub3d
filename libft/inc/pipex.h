/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:43:21 by aatieh            #+#    #+#             */
/*   Updated: 2024/12/25 00:29:32 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct s_pipex
{
	int	pipefd[2];
	int	children_num;
	int	last_id;
}		t_pipex;

char	*get_path(char **cmd, char **envp, int fd[2]);
int		wait_for_all(t_pipex *vars);
void	close_all(int fd1, int fd2);
void	free_all(char *str, char **split);
void	check_access(char *arg, t_pipex *vars, int is_first);

int		child_process(char *arg, int in_fd, int out_fd, char **envp);
void	first_process(char *argv[], int argc, t_pipex *vars, char **envp);
void	middle_process(char *argv[], int argc, t_pipex *vars, char **envp);
void	last_process(char *argv[], int argc, t_pipex *vars, char **envp);
void	limiter_process(char *argv[], int argc, t_pipex *vars, char **envp);

#endif
