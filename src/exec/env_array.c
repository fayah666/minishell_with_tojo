/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:47:42 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/05 10:03:19 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	count_env_vars(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

char	**env_list_to_array(t_env *env_list)
{
	char	**env_array;
	char	*env_var;
	int		i;
	int		count;

	count = count_env_vars(env_list);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env_list)
	{
		env_var = ft_strjoin(env_list->key, "=");
		if (!env_var)
			env_var = ft_strdup ("");
		if (!env_list->value)
			env_list->value = ft_strdup ("");
		env_array[i] = ft_strjoin(env_var, env_list->value);
		free(env_var);
		i++;
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
