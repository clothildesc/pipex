/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:31:30 by cscache           #+#    #+#             */
/*   Updated: 2025/06/17 16:32:14 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		**pipes;
	int		nb_cmds;
	pid_t	*pids;
	char	**cmds;
	char	**envp;
}	t_pipex;

//parsing
char	*check_path(char **path_folders, char *cmd);
char	*get_path(char *envp[], char *cmd);
char	**get_args(char *str);
void	init_pipes(t_pipex *p);
void	init_cmds(t_pipex *p, char *av[]);
void	init_pipex(t_pipex *p, int ac, char *av[], char *envp[]);

//files
int		open_infile(const char *infile);
int		open_outfile(const char *outfile);
void	open_files(const char *infile, const char *outfile);

//free
void	free_tab_chars(char **tab);
void	free_pipes(t_pipex *p);
void	free_cmds(t_pipex *p);

#endif