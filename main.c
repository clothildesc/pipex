/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:38:06 by cscache           #+#    #+#             */
/*   Updated: 2025/06/16 17:36:38 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	can_read(char *file)
{
	if (access(file, R_OK) == 0)
		return (1);
	return (0);
}

int	can_read(char *file)
{
	if (access(file, W_OK) == 0)
		return (1);
	return (0);
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
