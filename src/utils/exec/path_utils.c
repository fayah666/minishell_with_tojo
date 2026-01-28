/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 22:53:30 by hfandres          #+#    #+#             */
/*   Updated: 2026/01/22 11:26:08 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_cmd(char *cmd, t_all *all)
{
	if (ft_strcmp(cmd, "..") == 0)
	{
		exec_error(cmd, "command not found");
		all->exit_code = EXIT_COMMAND_NOT_FOUND;
		return (1);
	}
	if (ft_strcmp(cmd, ".") == 0)
	{
		exec_error(cmd, "filename argument required");
		write(2, ".: usage: . filename [arguments]\n", 34);
		all->exit_code = EXIT_SYNTAX_ERROR;
		return (1);
	}
	return (0);
}

static int	path_error(char *path, t_all *all)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		if (path[0] == '.' || path[0] == '/')
		{
			exec_error(path, "Is a directory");
			all->exit_code = 126;
		}
		else
		{
			exec_error(path, "command not found");
			all->exit_code = 127;
		}
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		exec_error(path, "Permission denied");
		all->exit_code = 126;
		return (1);
	}
	return (0);
}

char	*get_valid_path(char *cmd, t_all *all)
{
	char		*path;

	path = find_command_path(cmd, all->env_list);
	if (!path)
	{
		handle_path_error(cmd, all);
		all->exit_code = 127;
		return (NULL);
	}
	if (error_cmd(cmd, all))
	{
		free(path);
		return (NULL);
	}
	if (path_error(path, all))
	{
		free(path);
		return (NULL);
	}
	return (path);
}
