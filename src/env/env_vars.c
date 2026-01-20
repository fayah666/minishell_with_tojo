/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:10:38 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/20 20:15:33 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_new_env_var(t_env **env_list, char *key, char *value)
{
	char	*new_value;
	char	*dup_key;

	new_value = NULL;
	if (value)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return ;
	}
	dup_key = ft_strdup(key);
	if (!dup_key)
	{
		if (new_value)
			free(new_value);
		return ;
	}
	env_add_back(env_list, new_env_node(dup_key, new_value));
}

void	set_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*current;
	char	*new_value;

	if (!key || !env_list)
		return ;
	current = find_env_var(*env_list, key);
	if (current && value)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return ;
		if (current->value)
			free(current->value);
		current->value = new_value;
	}
	else
		add_new_env_var(env_list, key, value);
}

int	append_env_var(t_env **env_list, char *key, char *suffix)
{
	t_env	*current;
	char	*joined;

	if (!key || !env_list)
		return (-1);
	current = find_env_var(*env_list, key);
	if (!suffix)
		suffix = "";
	if (current && current->value && current->value[0])
	{
		joined = ft_strjoin(current->value, suffix);
		if (!joined)
			return (-1);
		if (current->value)
			free(current->value);
		current->value = joined;
		return (0);
	}
	else
		return (validate_and_set(key, suffix, env_list));
}

void	unset_env_var(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!key || !env_list || !*env_list)
		return ;
	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
