/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:47:48 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/21 01:44:08 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd_node(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->redirections = NULL;
	node->next = NULL;
	return (node);
}

int	is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == APPEND
		|| type == HERE_DOC);
}

int	syntax_error(char *token_content, t_all *all)
{
	write(2, "minishell: ", 11);
	write(2, "syntax Error near unexpected token `", 36);
	write(2, token_content, strlen(token_content));
	write(2, "'\n", 2);
	all->exit_code = EXIT_SYNTAX_ERROR;
	return (1);
}
