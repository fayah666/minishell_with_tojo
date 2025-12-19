/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 07:47:09 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/19 12:13:04 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static char	*get_valid_path(char **args, t_all *all)
{
	char		*path;
	struct stat	path_stat;

	path = find_command_path(args[0], all->env_list);
	if (!path)
	{
		handle_path_error(args[0], all);
		exit(all->exit_code);
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

static void parent_process(pid_t pid, t_all *all)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		all->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			all->exit_code = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			all->exit_code = 131;
		}
		else
			all->exit_code = 128 + WTERMSIG(status);
	}
}

/*
** This function is now the universal executor for any command in a subshell.
** It checks for ALL built-ins first, then falls back to execve.
*/
void child_process(t_cmd *cmd, t_all *all)
{
	int		builtin_status;
	char	*path;
	char	**envp;
	int		i;

	apply_heredoc_redirections(cmd);
	if (apply_redirections(cmd) != 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	i = 0;
	while (cmd->args[i] && is_whitespace_only(cmd->args[i]))
		i++;
	if (!cmd->args[i])
		exit(0);
	if (dispatch_all_builtins(&cmd->args[i], all, &builtin_status))
		exit(builtin_status);
	path = get_valid_path(&cmd->args[i], all);
	envp = env_list_to_array(all->env_list);
	execve(path, &cmd->args[i], envp);
	exec_error(path, NULL);
	free(path);
	free_array(envp);
	exit(126);
}

static void execute_simple_command(t_cmd *cmd, t_all *all)
{
	pid_t pid;
	int saved_fds[2];
	int is_complex;
	int i;
	char **args;

	save_std_fds(saved_fds);
	if (apply_redirections(cmd) != 0)
	{
		all->exit_code = 1;
		restore_std_fds(saved_fds);
		return;
	}
	args = cmd->args;
	if (args)
	{
		i = 0;
		while (args[i] && is_whitespace_only(args[i]))
			i++;
		args = &args[i];
	}
	is_complex = dispatch_complex_builtin(args, all);
	restore_std_fds(saved_fds);
	if (is_complex)
		return;
	setup_exec_signals();
	pid = fork();
	if (pid == -1)
	{
		exec_error("fork failed", NULL);
		all->exit_code = 1;
		setup_interactive_signals();
		return;
	}
	if (pid == 0)
	{
		setup_child_signals();
		child_process(cmd, all);
	}
	close_heredoc_fds(cmd);
	parent_process(pid, all);
	setup_interactive_signals();
}

static int prepare_execution(t_cmd *cmd_table, t_all *all)
{
	if (has_heredocs(cmd_table))
	{
		if (handle_heredocs(cmd_table, all) != 0)
		{
			if (all->heredoc_interrupted)
				return (130);
			all->exit_code = 1;
			return (1);
		}
	}
	return (0);
}

void executor(t_cmd *cmd_table, t_all *all)
{
	if (!cmd_table)
		return;
	if (prepare_execution(cmd_table, all) != 0)
		return ;
	if (!cmd_table->args || !cmd_table->args[0])
		return;
	if (!cmd_table->next)
		execute_simple_command(cmd_table, all);
	else
	{
		if (cmd_table->next && ft_strcmp (cmd_table->next->args[0], "exit") == 0)
		{
			all->exit_code = 127;
			return ;
		}
		execute_pipeline(cmd_table, all);
	}
}
