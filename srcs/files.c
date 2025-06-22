/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothildescache <clothildescache@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:37:36 by cscache           #+#    #+#             */
/*   Updated: 2025/06/22 23:37:59 by clothildesc      ###   ########.fr       */
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
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		perror("open outfile");
		return (-1);
	}
	return (fd);
}
