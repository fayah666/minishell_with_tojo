/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:54:06 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/15 12:00:22 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_cmd_table(t_cmd *head)
{
	t_cmd	*tmp_cmd;

	if (!head)
		return ;
	while (head)
	{
		tmp_cmd = head->next;
		free_redirections(head->redirections);
		free_args(head->args);
		free(head);
		head = tmp_cmd;
	}
}
