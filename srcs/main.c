/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:38:06 by cscache           #+#    #+#             */
/*   Updated: 2025/06/17 12:43:08 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* int	can_read(char *file)
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
} */

int	open_infile(const char *infile)
{
	int	fd;

	if (access(infile, F_OK | R_OK) == -1)
	{
		perror("access infile");
		return (-1);
	}
	else
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1)
		{
			perror("open infile");
			return (-1);
		}
	}
	return (fd);
}

int	open_outfile(const char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		perror("open outfile");
		return (-1);
	}
	return (fd);
}

void open_files(const char *infile, const char *outfile)

/* void	pipe_and_fork(char *str)
{
	int		pipefd[2];
	pid_t	pid;

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
} */


#include <stdio.h>

int	main(int ac, char *av[], char *envp[])
{
	char	**args;
	char	*cmd;

	if (ac != 5)
		return (1);
	else
	{
		args = get_args(av[1]);
		cmd = args[0];
		printf("%s\n", get_path(envp, args[0]));
	}
	return (0);
}
