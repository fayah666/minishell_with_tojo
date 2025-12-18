/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 08:17:35 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:42:58 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quotes(const char *input)
{
	char	quote_char;
	int		i;

	i = 0;
	quote_char = 0;
	while (input[i])
	{
		if (quote_char == 0 && (input[i] == '\'' || input[i] == '"'))
			quote_char = input[i];
		else if (quote_char != 0 && input[i] == quote_char)
			quote_char = 0;
		i++;
	}
	if (quote_char != 0)
		return (1);
	return (0);
}

static int	handle_special_char(const char *input, int i, t_token **list)
{
	if (input[i + 1] && input[i] == input[i + 1])
	{
		if (input[i] == '<')
			add_token_back(list, new_token(ft_strdup("<<"), HERE_DOC));
		else if (input[i] == '>')
			add_token_back(list, new_token(ft_strdup(">>"), APPEND));
		return (2);
	}
	else
	{
		if (input[i] == '<')
			add_token_back(list, new_token(ft_strdup("<"), REDIR_IN));
		else if (input[i] == '>')
			add_token_back(list, new_token(ft_strdup(">"), REDIR_OUT));
		else if (input[i] == '|')
			add_token_back(list, new_token(ft_strdup("|"), PIPE));
		return (1);
	}
}

static int	handle_word(const char *input, int i, t_token **list)
{
	int		start;
	char	*content;
	char	quote_char;

	start = i;
	while (input[i] && !isspace(input[i]) && !ft_strchr("|<>", input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote_char = input[i++];
			while (input[i] && input[i] != quote_char)
				i++;
			if (input[i] == quote_char)
				i++;
		}
		else
			i++;
	}
	content = (char *)malloc(sizeof(char) * (i - start + 1));
	if (!content)
		return (0);
	ft_strlcpy(content, &input[start], i - start + 1);
	content[i - start] = '\0';
	add_token_back(list, new_token(content, WORD));
	return (i - start);
}

t_token	*lexer(const char *input)
{
	t_token	*token_list;
	int		i;
	int		consumed;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		consumed = 0;
		if (isspace(input[i]))
		{
			i++;
			continue ;
		}
		if (ft_strchr("|<>", input[i]))
			consumed = handle_special_char(input, i, &token_list);
		else
			consumed = handle_word(input, i, &token_list);
		if (consumed == 0)
			break ;
		i += consumed;
	}
	return (token_list);
}
