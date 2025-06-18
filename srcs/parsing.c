/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:09:04 by cscache           #+#    #+#             */
/*   Updated: 2025/06/18 14:05:54 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_pipes(t_pipex *p)
{
	int	i;

	p->pipes = malloc(sizeof(int *) * (p->nb_cmds - 1));
	if (!p->pipes)
	{
		perror("malloc pipes");
		exit (1);
	}
	i = 0;
	while (i < p->nb_cmds - 1)
	{
		p->pipes[i] = malloc(sizeof(int) * 2);
		if (!p->pipes[i])
		{
			perror("malloc pipe pair");
			exit (1);
		}
		if (pipe(p->pipes[i]) == -1)
		{
			perror("pipe");
			exit (1);
		}
		i++;
	}
}

void	init_cmds(t_pipex *p, char *av[])
{
	int	i;

	p->cmds = malloc(sizeof(char *) * (p->nb_cmds + 1));
	if (!p->cmds)
	{
		perror("malloc cmds");
		exit (1);
	}
	i = 0;
	while (i < p->nb_cmds)
	{
		p->cmds[i] = av[i + 2];
		i++;
	}
	p->cmds[i] = NULL;
}

void	init_struct(t_pipex *p)
{
	p->fd_infile = -1;
	p->fd_outfile = -1;
	p->nb_cmds = 0;
	p->pipes = NULL;
	p->pids = NULL;
	p->cmds = NULL;
	p->envp = NULL;
}

void	init_pipex(t_pipex *p, int ac, char *av[], char *envp[])
{
	init_struct(p);
	p->envp = envp;
	p->nb_cmds = ac - 3;
	p->fd_infile = open_infile(av[1]);
	p->fd_outfile = open_outfile(av[ac - 1]);
	if (p->fd_infile < 0 || p->fd_outfile < 0)
		exit(1);
	init_pipes(p);
	init_cmds(p, av);
}

char	*check_path(char **path_folders, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (path_folders[i])
	{
		tmp = ft_strjoin(path_folders[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *envp[], char *cmd)
{
	int		i;
	char	**path_folders;
	char	*path;

	i = 0;
	path_folders = NULL;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	path_folders = ft_split(envp[i] + 5, ':');
	if (!path_folders)
		return (NULL);
	path = check_path(path_folders, cmd);
	free_tab_chars(path_folders);
	return (path);
}

char	**get_args(char *str)
{
	char	**args;

	args = ft_split(str, ' ');
	if (!args)
		return (free_tab_chars(args), NULL);
	return (args);
}
