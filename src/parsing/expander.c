/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:49:20 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 11:09:28 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handles the expansion of a '$' character.
static char	*handle_expansion(int *i, const char *content, t_all *all)
{
	int		start;
	char	*key;
	char	*value;

	(*i)++;
	if (content[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(all->exit_code));
	}
	if (!isalpha(content[*i]) && content[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (isalnum(content[*i]) || content[*i] == '_')
		(*i)++;
	key = ft_strndup(&content[start], *i - start);
	value = get_env_value(key, all->env_list);
	free(key);
	return (value);
}

// Helper to process one character or expansion and append to the new string.
static char	*process_and_append(char *new, const char *old, t_exp_state *st,
		t_all *a)
{
	if (old[st->i] == '$' && st->quote_char != '\'')
	{
		new = join_and_free(new, handle_expansion(&st->i, old, a));
	}
	else
	{
		new = append_char(new, old[st->i]);
		st->i++;
	}
	return (new);
}

// Check if content has quotes
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

// Processes a single token's content and returns the expanded string.
static char	*expand_token_content(char *content, t_all *all)
{
	char		*new_content;
	t_exp_state	state;

	new_content = ft_strdup("");
	state.i = 0;
	state.quote_char = 0;
	while (content[state.i])
	{
		if ((content[state.i] == '\'' || content[state.i] == '"')
			&& (state.quote_char == 0 || state.quote_char == content[state.i]))
		{
			if (state.quote_char == 0)
				state.quote_char = content[state.i];
			else
				state.quote_char = 0;
			state.i++;
		}
		else
			new_content = process_and_append(new_content, content, &state, all);
	}
	free(content);
	return (new_content);
}

// Main expander function, iterates through tokens.
int	expander(t_all *all)
{
	t_token	*current;

	current = all->tokens;
	while (current)
	{
		if (current->type == WORD)
		{
			current->has_quotes = content_has_quotes(current->content);
			current->content = expand_token_content(current->content, all);
		}
		current = current->next;
	}
	return (0);
}
