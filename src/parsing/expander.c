/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:49:20 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/18 14:17:59 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	content_has_quotes(const char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	expander(t_all *all)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;

	current = all->tokens;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == WORD && (!prev || prev->type != HERE_DOC))
		{
			current->has_quotes = content_has_quotes(current->content);
			current->content = expand_token_content(current->content, all);
			if (current->content[0] == '\0' && !current->has_quotes)
			{
				remove_token(all, prev, current, next);
				current = next;
				continue ;
			}
		}
		prev = current;
		current = next;
	}
	return (0);
}
