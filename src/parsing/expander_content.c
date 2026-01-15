/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:20:00 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/22 21:37:36 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!ft_isalpha(content[*i]) && content[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (ft_isalnum(content[*i]) || content[*i] == '_')
		(*i)++;
	key = ft_strndup(&content[start], *i - start);
	value = get_env_value(key, all->env_list);
	free(key);
	return (value);
}

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
			state->i++;
		}
		else
			new_content = process_and_append(new_content, content, state, all);
	}
	return (new_content);
}

char	*expand_token_content(char *content, t_all *all)
{
	char		*new_content;
	t_exp_state	state;
	char		*trunc;

	state.i = 0;
	state.quote_char = 0;
	new_content = expand_loop(content, all, &state);
	free(content);
	if (ft_strlen(new_content) > MAX_EXPAND_LEN)
	{
		trunc = ft_strndup(new_content, MAX_EXPAND_LEN);
		free(new_content);
		new_content = trunc;
	}
	return (new_content);
}
