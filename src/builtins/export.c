/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:24:46 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/20 20:24:40 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	print_export_error(char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	validate_and_set(char *key, char *value, t_env **env_list)
{
	char	*trimmed_value;

	trimmed_value = NULL;
	if (!is_valid_identifier(key))
		return (print_export_error(key));
	if (value)
	{
		if (value[0] == ' ')
			trimmed_value = ft_strdup(value + 1);
		else
			trimmed_value = ft_strdup(value);
	}
	set_env_var(env_list, key, trimmed_value);
	if (trimmed_value)
		free(trimmed_value);
	return (0);
}

static int	export_one(char *arg, t_env **env_list)
{
	char	*key;
	char	*value;

	if (!arg || !*arg)
		return (1);
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
		if (!split_assignment(arg, &key, &value, "+="))
			print_export_error(key);
		append_env_var(env_list, key, value);
		free(key);
		free(value);
	}
	else
	{
		if (!split_assignment(arg, &key, &value, "="))
			print_export_error(key);
		validate_and_set(key, value, env_list);
		free(key);
		free(value);
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
	signal(SIGPIPE, SIG_IGN);
	if (!args || !args[0])
	{
		signal(SIGPIPE, SIG_DFL);
		return (1);
	}
	if (!args[1])
	{
		print_sorted_env(*env_list);
		signal(SIGPIPE, SIG_DFL);
		return (0);
	}
	signal(SIGPIPE, SIG_DFL);
	return (export_with_args(args, env_list));
}
