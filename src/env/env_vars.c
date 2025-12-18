/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:10:38 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:39:40 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		new_value = NULL;
		if (value)
			new_value = ft_strdup(value);
		env_add_back(env_list, new_env_node(ft_strdup(key), new_value));
	}
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
