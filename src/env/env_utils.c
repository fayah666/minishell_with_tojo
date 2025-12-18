/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:12:52 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:39:40 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_var(t_env *head, const char *key)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	create_minimal_env(t_env **env_list)
{
	char	buffer[4096];
	char	*cwd;

	cwd = getcwd(buffer, 4096);
	if (cwd)
		env_add_back(env_list, new_env_node(ft_strdup("PWD"), ft_strdup(cwd)));
}

void	update_shell_level(t_env **env_list)
{
	t_env	*shlvl_node;
	int		current_level;

	shlvl_node = find_env_var(*env_list, "SHLVL");
	if (shlvl_node && shlvl_node->value)
	{
		current_level = atoi(shlvl_node->value);
		free(shlvl_node->value);
		shlvl_node->value = ft_itoa(current_level + 1);
	}
	else if (shlvl_node)
		shlvl_node->value = ft_strdup("1");
	else
		env_add_back(env_list, new_env_node(ft_strdup("SHLVL"), ft_strdup("1")));
}
