/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:02:41 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/15 12:35:58 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	prepare_execution(t_cmd *cmd_table, t_all *all)
{
	if (has_heredocs(cmd_table))
	{
		if (parse_heredoc(cmd_table, all) != 0)
		{
			if (all->heredoc_interrupted)
			{
				close_heredoc_fds(cmd_table);
				all->exit_code = EXIT_SIGINT;
				setup_interactive_signals();
				return (130);
			}
			all->exit_code = EXIT_GENERAL_ERROR;
			setup_interactive_signals();
			return (1);
		}
	}
	setup_interactive_signals();
	return (0);
}

static void	execute_simple_command(t_cmd *cmd, t_all *all)
{
	int		saved_fds[2];
	char	**args;

	if (handle_redirections_and_save_fds(cmd, all, saved_fds))
		return ;
	args = skip_whitespace_args(cmd->args);
	if (try_dispatch_complex_builtin(cmd, all, saved_fds))
		return ;
	fork_and_execute(cmd, all, args);
}

void	executor(t_cmd *cmd_table, t_all *all)
{
	if (!cmd_table)
		return ;
	if (prepare_execution(cmd_table, all) != 0)
	{
		close_heredoc_fds(cmd_table);
		return ;
	}
	setup_exec_signals();
	if (!cmd_table->next)
		execute_simple_command(cmd_table, all);
	else
		execute_pipeline(cmd_table, all);
	setup_interactive_signals();
	close_heredoc_fds(cmd_table);
}
