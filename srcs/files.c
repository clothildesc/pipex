/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:37:36 by cscache           #+#    #+#             */
/*   Updated: 2025/06/17 16:03:17 by cscache          ###   ########.fr       */
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

void	open_files(const char *infile, const char *outfile)
{
	int	fd_in;
	int	fd_out;

	fd_in = open_infile(infile);
	fd_out = open_outfile(outfile);
	if (fd_in < 0 || fd_out < 0)
		exit(1);
}
