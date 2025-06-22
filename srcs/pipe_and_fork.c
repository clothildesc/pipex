/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothildescache <clothildescache@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:52:41 by cscache           #+#    #+#             */
/*   Updated: 2025/06/23 00:04:31 by clothildesc      ###   ########.fr       */
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
		free_struct_and_exit(p);
	}
	if (pid == 0)
	{
		printf("Je suis dans l'enfant indice %d | PID = %d\n", i, pid);
		create_dup(p, i);
		execute_cmd(p, i);
	}
	printf("PID = %d\n", pid);
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

void	handle_here_doc(t_pipex *p, char *limiter)
{
	int		pipefd[2];
	char	*line;
	int		limiter_reached = 0;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), exit (1));
	write(1, "heredoc> ", 9);
	while ((line = get_next_line(0)))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			limiter_reached = 1;
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", 9);
	}
	close(pipefd[1]);
	p->fd_infile = pipefd[0];
	if (!limiter_reached)
		write(2, "warning: there is no delimiter\n", 32);
	if (line)
		free(line);
}

int	pipe_and_fork(t_pipex *p)
{
	int		i;
	int		status;

	i = 0;
	while (i < p->nb_cmds)
	{
		execute_child(p, i);
		i++;
	}
	close_pipes(p);
	i = 0;
	while (i < p->nb_cmds)
	{
		waitpid(p->pids[i], &status, 0);
		i++;
	}
	free_struct_and_exit(p);
	return (get_exit_code(status));
}
