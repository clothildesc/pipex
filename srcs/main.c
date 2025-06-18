/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:38:06 by cscache           #+#    #+#             */
/*   Updated: 2025/06/18 16:53:16 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	if (ac != 5)
		return (1);
	else
	{
		init_pipex(&pipex, ac, av, envp);
		pipe_and_fork(&pipex);
	}
	return (0);
}
