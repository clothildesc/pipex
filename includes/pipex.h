/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:31:30 by cscache           #+#    #+#             */
/*   Updated: 2025/06/20 18:57:07 by cscache          ###   ########.fr       */
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
// a enlever
# include <stdio.h>

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		**pipes;
	int		nb_cmds;
	pid_t	*pids;
	char	**cmds;
	char	**envp;
	int		here_doc;
}	t_pipex;

//init pipex
void	init_pipes(t_pipex *p);
void	init_cmds(t_pipex *p, char *av[]);
void	init_pids(t_pipex *p);
void	init_struct(t_pipex *p);
void	init_pipex(t_pipex *p, int ac, char *av[], char *envp[]);

//files
int		open_infile(const char *infile);
int		open_outfile(const char *outfile);

//parsing
char	*check_path(char **path_folders, char *cmd);
char	*get_path(char *envp[], char *cmd);
char	**get_args(const char *str);

//pipe and fork
void	close_pipes(t_pipex *p);
void	create_dup(t_pipex *p, int i);
void	execute_cmd(t_pipex *p, int i);
void	execute_child(t_pipex *p, int i);
void	cmd_not_found(char **args);
int		pipe_and_fork(t_pipex *p);
int		get_exit_code(int status);

//free
void	free_tab_chars(char **tab);
void	free_pipes(t_pipex *p);
void	free_struct_and_exit(t_pipex *p);

#endif