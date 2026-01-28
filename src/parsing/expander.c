/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:49:20 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/23 08:23:34 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_expansion(t_exp_state *st, const char *content, \
t_all *all, int at_start)
{
	int		start;
	char	*key;
	char	*value;

	st->i++;
	if (content[st->i] == '\'' || content[st->i] == '"')
		return (ft_strdup(""));
	if (content[st->i] == '?')
	{
		st->i++;
		return (ft_itoa(all->exit_code));
	}
	if (! (ft_isalnum(content[st->i]) || content[st->i] == '_'))
		return (ft_strdup("$"));
	start = st->i;
	while (ft_isalnum(content[st->i]) || content[st->i] == '_')
		st->i++;
	key = ft_strndup(&content[start], st->i - start);
	value = get_env_value(key, all->env_list);
	return (handle_value(key, value, st, at_start));
}

static char	*process_and_append(char *new, const char *old, t_exp_state *st,
		t_all *a)
{
	int	at_start;

	at_start = !st->passed_start;
	st->passed_start = 1;
	if (old[st->i] == '$' && st->quote_char != '\'')
	{
		if (st->quote_char != 0
			&& (old[st->i + 1] == '\'' || old[st->i + 1] == '"'))
		{
			new = append_char(new, old[st->i]);
			st->i++;
		}
		else
			new = join_and_free(new, handle_expansion(st, old, a, at_start));
	}
	else
	{
		new = append_char(new, old[st->i]);
		st->i++;
	}
	return (new);
}

static char	*expand_loop(const char *content, t_all *all, t_exp_state *state)
{
	char	*new_content;

	new_content = ft_strdup("");
	while (content[state->i])
	{
		if ((content[state->i] == '\'' || content[state->i] == '"')
			&& (state->quote_char == 0
				|| state->quote_char == content[state->i]))
		{
			if (state->quote_char == 0)
				state->quote_char = content[state->i];
			else
				state->quote_char = 0;
			state->passed_start = 1;
			state->i++;
		}
		else
			new_content = process_and_append(new_content, content, state, all);
	}
	return (new_content);
}

static char	*expand_token_content(char *content, t_all *all)
{
	char		*new_content;
	t_exp_state	state;
	char		*trunc;
	int			len;

	len = ft_strlen(content);
	init_exp_state(&state, content);
	new_content = expand_loop(content, all, &state);
	if (!(len > 0 && (content[len - 1] == '"' || content[len - 1] == '\'')))
	{
		len = ft_strlen(new_content);
		while (len > 0 && ft_isspace((unsigned char)new_content[len - 1]))
			new_content[--len] = '\0';
	}
	if (ft_strlen(new_content) > MAX_EXPAND_LEN)
	{
		trunc = ft_strndup(new_content, MAX_EXPAND_LEN);
		free(new_content);
		new_content = trunc;
	}
	free(content);
	return (new_content);
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
			current->has_quotes = (ft_strchr(current->content, '"') != NULL \
|| ft_strchr(current->content, '\'') != NULL);
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
