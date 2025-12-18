/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:59:27 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:38:31 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_exit_code(t_expand_state *state, t_all *all)
{
	char	*exit_str;

	exit_str = ft_itoa(all->exit_code);
	if (exit_str)
	{
		ft_strlcpy(&state->expanded[state->j], exit_str, ft_strlen(exit_str) + 1);
		state->j += ft_strlen(exit_str);
		free(exit_str);
	}
}

static void	append_var_value(t_expand_state *state, char *var_name, t_all *all)
{
	t_env	*env;
	char	*var_value;

	if (ft_strlen(var_name) > 0)
	{
		env = find_env_var(all->env_list, var_name);
		if (env && env->value)
			var_value = env->value;
		else
			var_value = "";
		ft_strlcpy(&state->expanded[state->j], var_value, ft_strlen(var_value) + 1);
		state->j += ft_strlen(var_value);
	}
}

static void	extract_and_append_var(t_expand_state *state, t_all *all)
{
	char	var_name[256];
	int		k;

	state->i++;
	if (state->line[state->i] == '?')
	{
		append_exit_code(state, all);
		state->i++;
		return ;
	}
	k = 0;
	while (state->line[state->i] && (isalnum(state->line[state->i])
			|| state->line[state->i] == '_'))
		var_name[k++] = state->line[state->i++];
	var_name[k] = '\0';
	append_var_value(state, var_name, all);
}

char	*expand_heredoc_line(char *line, t_all *all)
{
	t_expand_state	state;

	if (!line)
		return (NULL);
	state.expanded = malloc(ft_strlen(line) * 2 + 1);
	if (!state.expanded)
		return (NULL);
	state.line = line;
	state.i = 0;
	state.j = 0;
	while (state.line[state.i])
	{
		if (state.line[state.i] == '$' && state.line[state.i + 1])
			extract_and_append_var(&state, all);
		else
			state.expanded[state.j++] = state.line[state.i++];
	}
	state.expanded[state.j] = '\0';
	return (state.expanded);
}

char	*remove_quotes(char *str)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
