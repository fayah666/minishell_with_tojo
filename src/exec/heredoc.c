/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:21:14 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/02 13:56:15 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_single_heredoc(t_redir *redir, t_all *all)
{
	t_hdoc_data	data;
	pid_t		pid;

	if (init_heredoc_data(&data, redir) != 0)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		cleanup_heredoc_data(&data, 0);
		return (1);
	}
	if (pid == 0)
		heredoc_child_process(&data, redir, all);
	return (heredoc_parent_process(pid, &data, redir, all));
}

int	handle_heredocs(t_cmd *cmd_list, t_all *all)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == HERE_DOC)
			{
				if (process_single_heredoc(redir, all) != 0)
				{
					setup_interactive_signals();
					return (1);
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	setup_interactive_signals();
	return (0);
}

int	has_heredocs(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == HERE_DOC)
				return (1);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
