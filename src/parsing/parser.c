/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:24:34 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/18 11:19:58 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*handle_pipe(t_token **tok, t_cmd *cmd, t_all *all)
{
	if (!cmd->args && !cmd->redirections)
		return (syntax_error("|", all), NULL);
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type == PIPE)
		return (syntax_error("|", all), NULL);
	cmd->next = new_cmd_node();
	if (!cmd->next)
		return (NULL);
	return (cmd->next);
}

/*
** Creates and adds a new redirection node to the command's redirection list.
*/
static int	create_and_add_redir(t_cmd *cmd, t_token *tok, t_type redir_type)
{
	t_redir	*redir;
	t_redir	*current;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (1);
	redir->filename = ft_strdup(tok->content);
	redir->type = redir_type;
	redir->heredoc_fd = -1;
	redir->is_quoted = 0;
	if (redir_type == HERE_DOC)
		redir->is_quoted = tok->has_quotes;
	redir->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = redir;
	else
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
	return (0);
}

/*
** Handles a redirection token by validating it and creating the redir node.
*/
static int	handle_redirection(t_token **tok, t_cmd *cmd, t_all *all)
{
	t_type	redir_type;

	redir_type = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != WORD)
	{
		if (*tok)
			return (syntax_error((*tok)->content, all));
		else
			return (syntax_error("newline", all));
	}
	return (create_and_add_redir(cmd, *tok, redir_type));
}

static t_cmd	*process_tokens(t_all *all, t_cmd *cmd_list)
{
	t_token	*current_token;
	t_cmd	*current_cmd;

	current_token = all->tokens;
	current_cmd = cmd_list;
	while (current_token)
	{
		if (is_redir(current_token->type))
		{
			if (handle_redirection(&current_token, current_cmd, all))
				return (NULL);
		}
		else if (current_token->type == WORD)
			add_arg_to_cmd(current_cmd, current_token->content);
		else if (current_token->type == PIPE)
		{
			current_cmd = handle_pipe(&current_token, current_cmd, all);
			if (!current_cmd)
				return (NULL);
			continue ;
		}
		current_token = current_token->next;
	}
	return (cmd_list);
}

t_cmd	*parser(t_all *all)
{
	t_cmd	*cmd_list_head;
	t_cmd	*result;

	if (!all->tokens)
		return (NULL);
	if (all->tokens->type == PIPE)
	{
		syntax_error("|", all);
		return (NULL);
	}
	cmd_list_head = new_cmd_node();
	if (!cmd_list_head)
		return (NULL);
	result = process_tokens(all, cmd_list_head);
	if (!result)
	{
		free_cmd_table(cmd_list_head);
		return (NULL);
	}
	return (result);
}
