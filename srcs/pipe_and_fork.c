/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:52:41 by cscache           #+#    #+#             */
/*   Updated: 2025/06/23 12:20:57 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds - 1)
	{
		close(p->pipes[i][0]);
		close(p->pipes[i][1]);
		i++;
	}
}

void	create_dup(t_pipex *p, int i)
{
	if (i == 0)
	{
		dup2(p->fd_infile, 0);
		dup2(p->pipes[i][1], 1);
	}
	else if (i == p->nb_cmds - 1)
	{
		dup2(p->pipes[i - 1][0], 0);
		dup2(p->fd_outfile, 1);
	}
	else
	{
		dup2(p->pipes[i - 1][0], 0);
		dup2(p->pipes[i][1], 1);
	}
	close_pipes(p);
}

void	execute_child(t_pipex *p, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_struct(p);
		exit_code(1);
	}
	if (pid == 0)
	{
		create_dup(p, i);
		execute_cmd(p, i);
	}
	p->pids[i] = pid;
}

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

int	pipe_and_fork(t_pipex *p)
{
	int		i;
	int		status;
	pid_t	current_pid;
	int		exit_code;

	i = 0;
	exit_code = 0;
	while (i < p->nb_cmds)
	{
		execute_child(p, i);
		i++;
	}
	close_pipes(p);
	i = 0;
	while (i < p->nb_cmds)
	{
		current_pid = waitpid(p->pids[i], &status, 0);
		if (current_pid == p->pids[p->nb_cmds - 1])
			exit_code = get_exit_code(status);
		i++;
	}
	free_struct(p);
	return (exit_code);
}
