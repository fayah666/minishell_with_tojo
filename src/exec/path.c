/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:34:01 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/18 10:01:38 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper to get the value of PATH from your env list.
static char	*get_path_var(t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, "PATH") == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

// Helper to free the array created by ft_split.
static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/*
** Searches for the command in the provided path directories.
*/
static char	*search_in_path(const char *cmd, char **paths)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = -1;
	while (paths && paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

/*
** Main function to find the command path.
*/
char	*find_command_path(const char *cmd, t_env *env_list)
{
	char	**paths;
	char	*path_var;
	char	*executable_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_var = get_path_var(env_list);
	if (!path_var)
	    return (NULL);
	paths = ft_split(path_var, ':');
	executable_path = search_in_path(cmd, paths);
	free_paths(paths);
	return (executable_path);
}
