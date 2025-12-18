/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:41:54 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:40:22 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles the error case when a command path is not found.
** Differentiates between a command not in PATH and a path that does not exist.
*/
void	handle_path_error(char *cmd_str, t_all *all)
{
    if (ft_strchr(cmd_str, '/'))
        exec_error(cmd_str, "No such file or directory");
    else
        exec_error(cmd_str, "command not found");
    all->exit_code = 127;
}

/*
** Apply heredoc redirections by duplicating the pipe fd to stdin
*/
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

/*
** Close all heredoc fds in the parent after forking
*/
void	close_heredoc_fds(t_cmd *cmd)
{
	t_redir	*redir;

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
}
