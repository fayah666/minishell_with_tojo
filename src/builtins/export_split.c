/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:55:55 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/19 11:29:44 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static char	*extract_key(char *arg, char *equals)
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

static int	count_len(const char *str)
{
	int	len;
	int	in_space;

	len = 0;
	in_space = 1;
	while (*str)
	{
		if (ft_isspace((unsigned char)*str))
			in_space = 1;
		else
		{
			if (in_space && len > 0)
			{

				len++;
			}
			len++;
			in_space = 0;
		}
		str++;
	}
	printf ("len calculated: %d\n", len);
	return (len);
}

char	*normalize_whitespace(const char *str)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	new_str = malloc(count_len(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace((unsigned char)str[i]))
			i++;
		if (str[i])
		{
			if (j > 0)
				new_str[j++] = ' ';
			while (str[i] && !ft_isspace((unsigned char)str[i]))
				new_str[j++] = str[i++];
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

int	split_assignment(char *arg, char **key, char **value)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
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
	*value = normalize_whitespace(equals + 1);
	if (!*value)
	{
		free(*key);
		*key = NULL;
		return (0);
	}
	return (1);
}
