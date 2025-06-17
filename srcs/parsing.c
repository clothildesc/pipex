/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:09:04 by cscache           #+#    #+#             */
/*   Updated: 2025/06/17 12:12:32 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_folders(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
}

char	*check_path(char **path_folders, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (path_folders[i])
	{
		tmp = ft_strjoin(path_folders[i], "/");
		if (!tmp)
			return (free_folders(path_folders, i), NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (free_folders(path_folders, i), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_folders(path_folders, i);
	return (NULL);
}

char	*get_path(char *envp[], char *cmd)
{
	int		i;
	char	**path_folders;
	char	*path;

	i = 0;
	path_folders = NULL;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	path_folders = ft_split(envp[i] + 5, ':');
	if (!path_folders)
		return (NULL);
	path = check_path(path_folders, cmd);
	return (path);
}

char	**get_args(char *str)
{
	char	**args;

	args = ft_split(str, ' ');
	if (!args)
		return (NULL);
	return (args);
}
