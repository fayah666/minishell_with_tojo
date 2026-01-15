/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:03:50 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/15 12:26:54 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

char	**skip_whitespace_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (NULL);
	while (args[i] && is_whitespace_only(args[i]))
		i++;
	return (&args[i]);
}

int	handle_redirections_and_save_fds(t_cmd *cmd, t_all *all, int saved_fds[2])
{
	saved_fds[0] = -1;
	saved_fds[1] = -1;
	if (cmd->redirections)
		save_std_fds(saved_fds);
	if (apply_redirections(cmd) != 0)
	{
		all->exit_code = EXIT_GENERAL_ERROR;
		restore_std_fds(saved_fds);
		return (1);
	}
	return (0);
}

int	try_dispatch_complex_builtin(t_cmd *cmd, t_all *all, int saved_fds[2])
{
	int	is_complex;

	is_complex = dispatch_complex_builtin(cmd, all);
	restore_std_fds(saved_fds);
	return (is_complex);
}

void	fork_and_execute(t_cmd *cmd, t_all *all, char **args)
{
	pid_t	pid;

	(void)args;
	setup_exec_signals();
	pid = fork();
	if (pid == -1)
	{
		exec_error("fork failed", NULL);
		all->exit_code = EXIT_GENERAL_ERROR;
		setup_interactive_signals();
		return ;
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
