/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:38:06 by cscache           #+#    #+#             */
/*   Updated: 2025/06/17 16:38:04 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	fork_cmd(int pipefd[], char *cmd, char *envp[])
{
	pid_t	pid;
	char	**args;
	char	*path;

	args = get_args(cmd);
	if (!args)
		return (free_all(args), -1);
	path = get_path(envp, args[0]);
	if (!path)
		return (free(path), -1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		execve(args[0], args, envp);
	}
	if (pid > 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
	}
}

void	pipe_and_fork(char *str)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

#include <stdio.h>

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	if (ac != 5)
		return (1);
	else
		init_pipex(&pipex, ac, av, envp);
	free_pipes(&pipex);
	free_cmds(&pipex);
	return (0);
}
