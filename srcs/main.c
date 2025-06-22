/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clothildescache <clothildescache@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:38:06 by cscache           #+#    #+#             */
/*   Updated: 2025/06/22 23:54:42 by clothildesc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;
	int		code;

	if ((av[1] && ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
		|| (av[1] && ft_strncmp(av[1], "here_doc", 9) != 0 && ac < 5))
		return (write(2, "invalid number of arguments\n", 29), 1);
	init_pipex(&pipex, ac, av, envp);
	if (pipex.heredoc)
		handle_heredoc(av[2], &pipex);
	code = pipe_and_fork(&pipex);
	return (code);
}
