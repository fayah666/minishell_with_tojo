/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:54:06 by torakoto          #+#    #+#             */
/*   Updated: 2025/11/26 17:54:32 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees the linked list of redirections for a single command.
*/
static void	free_redirections(t_redir *redir_list)
{
	t_redir	*tmp;

	while (redir_list)
	{
		tmp = redir_list->next;
		free(redir_list->filename);
		free(redir_list);
		redir_list = tmp;
	}
}

/*
** Frees the null-terminated array of arguments for a single command.
*/
static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/*
** Frees the entire command table, including all sub-structures.
*/
void	free_cmd_table(t_cmd *head)
{
	t_cmd	*tmp_cmd;

	while (head)
	{
		tmp_cmd = head->next;
		free_redirections(head->redirections);
		free_args(head->args);
		free(head);
		head = tmp_cmd;
	}
}
