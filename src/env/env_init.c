/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:27:18 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:40:22 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **head, t_env *new_node)
{
	t_env	*current;

	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static void	parse_and_add_node(const char *env_str, t_env **env_list)
{
	char	*key;
	char	*value;
	char	*eq_ptr;
	int		key_len;

	eq_ptr = ft_strchr(env_str, '=');
	if (eq_ptr)
	{
		key_len = eq_ptr - env_str;
		key = (char *)malloc(key_len + 1);
		if (!key)
			return ;
		ft_strlcpy(key, env_str, key_len + 1);
		key[key_len] = '\0';
		value = ft_strdup(eq_ptr + 1);
	}
	else
	{
		key = ft_strdup(env_str);
		value = NULL;
	}
	env_add_back(env_list, new_env_node(key, value));
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	i = 0;
	if (envp && envp[0])
	{
		while (envp[i])
		{
			parse_and_add_node(envp[i], &env_list);
			i++;
		}
	}
	else
		create_minimal_env(&env_list);
	update_shell_level(&env_list);
	return (env_list);
}

// Check if a string is a valid shell identifier
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!(isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
