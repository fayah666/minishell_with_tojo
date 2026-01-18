/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:34:01 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/18 14:01:20 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_valid_path(char *cmd, t_all *all)
{
	struct stat	path_stat;
	char		*path;

	path = find_command_path(cmd, all->env_list);
	if (!path)
	{
		handle_path_error(cmd, all);
		all->exit_code = 127;
		return (NULL);
	}
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		exec_error(path, "Is a directory");
		all->exit_code = 126;
		free(path);
		return (NULL);
	}
	if (access(path, X_OK) != 0)
	{
		exec_error(path, "Permission denied");
		all->exit_code = 126;
		free(path);
		return (NULL);
	}
	return (path);
}
