/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:55:55 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/20 19:54:57 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

char	*extract_key(char *arg, char *equals)
{
	char	*key;
	size_t	key_len;

	key_len = equals - arg;
	if (key_len == 0)
		return (NULL);
	key = malloc(key_len + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, arg, key_len + 1);
	key[key_len] = '\0';
	return (key);
}

int	split_assignment(char *arg, char **key, char **value, char *operator)
{
	char	*equals;

	equals = ft_strnstr(arg, operator, ft_strlen(arg));
	if (!equals)
	{
		*key = ft_strdup(arg);
		*value = NULL;
		return (*key != NULL);
	}
	*key = extract_key(arg, equals);
	if (!*key)
	{
		*value = NULL;
		return (0);
	}
	*value = ft_strdup(equals + ft_strlen(operator));
	if (!*value)
	{
		free(*key);
		*key = NULL;
		return (0);
	}
	return (1);
}
