/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:40:38 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/19 10:24:14 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			if (env_list->value)
				return (ft_strdup(env_list->value));
			else
				return (ft_strdup(""));
		}
		env_list = env_list->next;
	}
	return (ft_strdup(""));
}

char	*append_char(char *str, char c)
{
	int		len;
	char	*new_str;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	if (str)
		ft_strlcpy(new_str, str, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

void	remove_token(t_all *all, t_token *prev, t_token *current, t_token *next)
{
	if (prev)
		prev->next = next;
	else
		all->tokens = next;
	free(current->content);
	free(current);
}
