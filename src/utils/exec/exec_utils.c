/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:41:54 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/10 10:33:09 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_path_error(char *cmd_str, t_all *all)
{
	if (ft_strchr(cmd_str, '/'))
		exec_error(cmd_str, "No such file or directory");
	else
		exec_error(cmd_str, "command not found");
	all->exit_code = EXIT_COMMAND_NOT_FOUND;
}

void	apply_heredoc_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == HERE_DOC && redir->heredoc_fd != -1)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
		}
		redir = redir->next;
	}
}

void	close_heredoc_fds(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == HERE_DOC && redir->heredoc_fd != -1)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
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
