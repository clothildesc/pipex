/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:08:16 by cscache           #+#    #+#             */
/*   Updated: 2025/06/23 10:30:05 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	is_here_doc(const char *str)
{
	if (ft_strncmp(str, "here_doc", 9) == 0)
		return (1);
	return (0);
}

void	read_line(char *line, int *pipefd, char *limiter)
{
	int		limiter_reached;

	limiter_reached = 0;
	while (line)
	{
		write(1, "heredoc> ", 9);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			limiter_reached = 1;
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	if (!limiter_reached)
		write(2, "warning: there is no delimiter\n", 32);
	if (line)
		free(line);
}

void	handle_here_doc(t_pipex *p, char *limiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	read_line(line, pipefd, limiter);
	close(pipefd[1]);
	p->fd_infile = pipefd[0];
}
