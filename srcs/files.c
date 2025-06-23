/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:37:36 by cscache           #+#    #+#             */
/*   Updated: 2025/06/23 15:53:01 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	open_outfile(const char *outfile, t_pipex *p)
{
	int	fd;

	if (p->here_doc)
		fd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open outfile");
		return (-1);
	}
	return (fd);
}
