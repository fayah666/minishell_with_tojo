/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:05:06 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/15 12:35:12 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	free_all_and_exit(t_all *all, int exit_code)
{
	free_cmd_table(all->cmd_table);
	free_env_list(all->env_list);
	free_token_list(all->tokens);
	exit(exit_code);
}

char	*get_valid_path(t_cmd *cmd, t_all *all)
{
	char		*path;
	struct stat	path_stat;

	path = find_command_path(cmd->args[0], all->env_list);
	if (!path)
	{
		handle_path_error(cmd->args[0], all);
		free_all_and_exit(all, all->exit_code);
	}
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		exec_error(path, "Is a directory");
		free(path);
		exit(126);
	}
	if (access(path, X_OK) != 0)
	{
		exec_error(path, "Permission denied");
		free(path);
		exit(126);
	}
	return (path);
}

void	parent_process(pid_t pid, t_all *all)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		all->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			all->exit_code = EXIT_SIGINT;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			all->exit_code = EXIT_SIGQUIT;
		}
		else
			all->exit_code = 128 + WTERMSIG(status);
	}
}

void	child_process(t_cmd *cmd, t_all *all)
{
	int		builtin_status;
	char	*path;
	char	**envp;
	int		i;

	apply_heredoc_redirections(cmd);
	close_heredoc_fds(all->cmd_table);
	if (apply_redirections(cmd) != 0)
		free_all_and_exit (all, 1);
	if (!cmd->args || !cmd->args[0])
		free_all_and_exit (all, 0);
	i = 0;
	while (cmd->args[i] && is_whitespace_only(cmd->args[i]))
		i++;
	if (!cmd->args[i])
		free_all_and_exit (all, 1);
	if (dispatch_all_builtins(cmd, all, &builtin_status))
		free_all_and_exit(all, builtin_status);
	path = invalid_path(cmd->args[0], all);
	if (!path)
		free_all_and_exit(all, all->exit_code);
	envp = env_list_to_array(all->env_list);
	execve(path, &cmd->args[i], envp);
	exec_error(path, NULL);
	free(path);
	free_array(envp);
	exit(126);
}
