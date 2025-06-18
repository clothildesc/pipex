/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:38:06 by cscache           #+#    #+#             */
/*   Updated: 2025/06/18 14:27:10 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

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

void	execute_child(t_pipex *p, int i)
{
	pid_t	pid;
	char	**args;
	char	*cmd_path;

	printf("Je suis dans l'enfant indice %d\n", i);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_struct_and_exit(p);
	}
	if (pid == 0)
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
		args = get_args(p->cmds[i]);
		if (!args)
			free_struct_and_exit(p);
		cmd_path = get_path(p->envp, args[0]);
		if (!cmd_path)
			return (free_tab_chars(args), free_struct_and_exit(p));
		execve(cmd_path, args, p->envp);
		perror("execve");
		free(cmd_path);
		free_tab_chars(args);
		free_struct_and_exit(p);
	}
	p->pids[i] = pid;
}

void	pipe_and_fork(t_pipex *p)
{
	int	i;

	p->pids = malloc(sizeof(t_pipex) * p->nb_cmds);
	if (!p->pids)
	{
		perror("pids malloc");
		free_struct_and_exit(p);
	}
	i = 0;
	while (i < p->nb_cmds)
	{
		execute_child(p, i);
		i++;
	}
	close_pipes(p);
	printf("Je suis dans le parent");
	i = 0;
	while (i < p->nb_cmds)
	{
		waitpid(p->pids[i], NULL, 0);
		i++;
	}
	close(p->fd_infile);
	close(p->fd_outfile);
	free_struct_and_exit(p);
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	if (ac != 5)
		return (1);
	else
	{
		init_pipex(&pipex, ac, av, envp);
		pipe_and_fork(&pipex);
	}
	return (0);
}
