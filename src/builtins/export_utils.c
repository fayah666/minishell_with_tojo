/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:50:52 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:19:01 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static void	print_export_var(t_env *var)
{
	printf("declare -x %s", var->key);
	if (var->value)
		printf("=\"%s\"", var->value);
	printf("\n");
}

static void	init_printed_array(t_env *env_list, int *printed, int *count)
{
	t_env	*current;

	*count = 0;
	current = env_list;
	while (current && *count < 1024)
	{
		printed[(*count)++] = 0;
		current = current->next;
	}
}

static t_env	*find_smallest_unprinted(t_env *env_list, int *printed,
		int count)
{
	t_env	*current;
	t_env	*smallest;
	int		j;

	smallest = NULL;
	current = env_list;
	j = 0;
	while (current && j < count)
	{
		if (!printed[j] && (!smallest || ft_strcmp(current->key,
					smallest->key) < 0))
			smallest = current;
		current = current->next;
		j++;
	}
	return (smallest);
}

static void	mark_as_printed(t_env *env_list, t_env *smallest, int *printed,
		int count)
{
	t_env	*current;
	int		j;

	current = env_list;
	j = 0;
	while (current && j < count)
	{
		if (current == smallest)
		{
			printed[j] = 1;
			break ;
		}
		current = current->next;
		j++;
	}
}

void	print_sorted_env(t_env *env_list)
{
	int		printed[1024];
	int		count;
	int		i;
	t_env	*smallest;

	init_printed_array(env_list, printed, &count);
	i = 0;
	while (i < count)
	{
		smallest = find_smallest_unprinted(env_list, printed, count);
		if (smallest)
		{
			print_export_var(smallest);
			mark_as_printed(env_list, smallest, printed, count);
		}
		i++;
	}
}
