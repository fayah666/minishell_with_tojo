/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:20:00 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/22 21:20:00 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_with_eq(const char *env_str, char **key, char **value)
{
	char	*eq_ptr;
	int		key_len;

	eq_ptr = ft_strchr(env_str, '=');
	key_len = eq_ptr - env_str;
	*key = (char *)malloc(key_len + 1);
	if (!*key)
		return (1);
	ft_strlcpy(*key, env_str, key_len + 1);
	(*key)[key_len] = '\0';
	*value = ft_strdup(eq_ptr + 1);
	if (!*value)
	{
		free(*key);
		return (1);
	}
	return (0);
}

static int	parse_without_eq(const char *env_str, char **key, char **value)
{
	*key = ft_strdup(env_str);
	if (!*key)
		return (1);
	*value = NULL;
	return (0);
}

static int	parse_env_key_value(const char *env_str, char **key, char **value)
{
	char	*eq_ptr;

	eq_ptr = ft_strchr(env_str, '=');
	if (eq_ptr)
		return (parse_with_eq(env_str, key, value));
	else
		return (parse_without_eq(env_str, key, value));
}

void	parse_and_add_node(const char *env_str, t_env **env_list)
{
	char	*key;
	char	*value;

	if (parse_env_key_value(env_str, &key, &value) == 0)
		env_add_back(env_list, new_env_node(key, value));
}
