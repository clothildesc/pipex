/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:52:41 by cscache           #+#    #+#             */
/*   Updated: 2025/06/19 13:32:11 by cscache          ###   ########.fr       */
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

void	cmd_not_found(char **args)
{
	ft_putstr_fd("command not found : ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd("\n", 2);
	free_tab_chars(args);
	exit(127);
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
		create_dup(p, i);
		args = get_args(p->cmds[i]);
		if (!args)
			exit(1);
		cmd_path = get_path(p->envp, args[0]);
		if (!cmd_path)
			cmd_not_found(args);
		execve(cmd_path, args, p->envp);
		perror("execve");
		return (free(cmd_path), free_tab_chars(args), exit(126));
	}
	p->pids[i] = pid;
}

void	pipe_and_fork(t_pipex *p)
{
	int	i;

	p->pids = malloc(sizeof(pid_t) * p->nb_cmds);
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
