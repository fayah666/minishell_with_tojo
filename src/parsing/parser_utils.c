/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:47:48 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:39:40 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Creates a new, initialized t_cmd node.
*/
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

/*
** Adds a new argument to a command's args array by reallocating it.
*/
int	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (1);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	return (0);
}

/*
** Checks if a token type is a redirection.
*/
int	is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == APPEND
		|| type == HERE_DOC);
}

/*
** Prints a syntax error message and sets the exit code.
*/
int	syntax_error(char *token_content, t_all *all)
{
	printf("minishell: syntax error near unexpected token `%s'\n",
		token_content);
	all->exit_code = 2;
	return (1);
}
