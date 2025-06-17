/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:38:06 by cscache           #+#    #+#             */
/*   Updated: 2025/06/17 10:44:05 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	can_read(char *file)
{
	if (access(file, R_OK) == 0)
		return (1);
	return (0);
}

int	can_write(char *file)
{
	if (access(file, W_OK) == 0)
		return (1);
	return (0);
}

char	**get_path_folders(char *envp[], char *cmd)
{
	int		i;
	char	**path_folders;
	char	*path_folder;

	i = 0;
	path_folders = NULL;
	path_folder = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path_folders = ft_split(envp[i], ':');
	i = 0;
	while (path_folders[i])
	{
		path_folder = ft_strjoin(path_folders[i], cmd);
		if (!path_folder)
			free(path_folder);
		if (access(path_folders, F_OK | W_OK) == 0)
			return (path_folders);
		i++;
	}
	return (NULL);
}

char	get_good_path_folder(char *cmd)
{
	
}

int	main(int ac, char *av[], char *envp[])
{
	int		pipefd[2];
	pid_t	pid;

	if (ac != 4)
		return (1);
	else
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
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
			char *args[] = {"/bin/ls", "-l", NULL};
			execve("/bin/ls", args, envp);
		}
		if (pid > 0)
		{
			dup2(pipefd[1], 1);
			close(pipefd[0]);
		}
	}
	return (0);
}
