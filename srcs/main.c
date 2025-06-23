/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:38:06 by cscache           #+#    #+#             */
/*   Updated: 2025/06/23 10:21:36 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;
	int		code;

	if ((av[1] && is_here_doc(av[1]) && ac < 6) \
	|| (av[1] && !is_here_doc(av[1]) && ac < 5))
		return (write(2, "invalid nb of arguments\n", 25), 1);
	init_pipex(&pipex, ac, av, envp);
	if (pipex.here_doc)
		handle_heredoc(av[2], &pipex);
	code = pipe_and_fork(&pipex);
	return (code);
}
