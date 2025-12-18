/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:24:46 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:38:31 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static void	print_export_error(char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

static int	validate_and_set(char *key, char *value, t_env **env_list)
{
	if (!key || !is_valid_identifier(key))
	{
		if (key)
			free(key);
		if (value)
			free(value);
		return (1);
	}
	set_env_var(env_list, key, value);
	if (value)
		free(value);
	free(key);
	return (0);
}

static int	export_one(char *arg, t_env **env_list)
{
	char	*key;
	char	*value;

	if (!arg || !*arg)
		return (1);
	if (!split_assignment(arg, &key, &value))
	{
		print_export_error(arg);
		return (1);
	}
	if (validate_and_set(key, value, env_list) != 0)
	{
		print_export_error(arg);
		return (1);
	}
	return (0);
}

static int	export_with_args(char **args, t_env **env_list)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (export_one(args[i], env_list) != 0)
			status = 1;
		i++;
	}
	return (status);
}

int	ft_export(char **args, t_env **env_list)
{
	if (!args || !args[0])
		return (1);
	if (!args[1])
	{
		print_sorted_env(*env_list);
		return (0);
	}
	return (export_with_args(args, env_list));
}
