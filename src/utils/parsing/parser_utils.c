/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:47:48 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/15 12:15:48 by hfandres         ###   ########.fr       */
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
	printf("minishell: syntax error near unexpected token `%s'\n",
		token_content);
	all->exit_code = EXIT_SYNTAX_ERROR;
	return (1);
}
