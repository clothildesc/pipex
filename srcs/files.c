/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:37:36 by cscache           #+#    #+#             */
/*   Updated: 2025/06/18 16:55:09 by cscache          ###   ########.fr       */
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
