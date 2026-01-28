/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:00:16 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/23 08:49:59 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_collapsed_str(char *new_str, const char *str, int *j)
{
	int	i;
	int	in_space;

	i = 0;
	in_space = 0;
	while (str[i])
	{
		if (ft_isspace((unsigned char)str[i]))
		{
			if (!in_space)
			{
				new_str[(*j)++] = ' ';
				in_space = 1;
			}
		}
		else
		{
			new_str[(*j)++] = str[i];
			in_space = 0;
		}
		i++;
	}
}

static char	*collapse_whitespace(const char *str)
{
	char	*new_str;
	int		j;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	j = 0;
	build_collapsed_str(new_str, str, &j);
	new_str[j] = '\0';
	return (new_str);
}

char	*normalize_whitespace(char *str, int strip_leading)
{
	const char	*start;
	char		*result;

	if (!str)
		return (NULL);
	start = str;
	if (strip_leading)
		while (*start && ft_isspace((unsigned char)*start))
			start++;
	result = collapse_whitespace(start);
	return (result);
}

void	init_exp_state(t_exp_state *state, char *content)
{
	(void)content;
	state->i = 0;
	state->quote_char = 0;
	state->passed_start = 0;
}
