/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:09:28 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/24 16:58:05 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	handle_error(const char *target, char *old_pwd, char *target_copy)
{
	if (chdir(target) != 0)
	{
		write(2, "minishell: cd: ", 15);
		perror(target);
		free (old_pwd);
		if (target_copy)
			free(target_copy);
		return (1);
	}
	return (0);
}

static int	cd_execute(char *target, char *old_pwd, \
t_env **env_list, char **args)
{
	char	*target_copy;

	target_copy = NULL;
	if (args[1] && ft_strcmp(args[1], "-") == 0)
	{
		target_copy = ft_strdup(target);
		if (!target_copy)
		{
			free(old_pwd);
			return (1);
		}
	}
	if (handle_error(target, old_pwd, target_copy))
		return (1);
	update_pwd_vars(env_list, old_pwd);
	if (target_copy)
	{
		printf("%s\n", target_copy);
		free(target_copy);
	}
	free (old_pwd);
	return (0);
}

int	ft_cd(char **args, t_env **env_list)
{
	char	*target;
	char	*old_pwd;

	if (args[1] && args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	old_pwd = update_old_pwd(env_list);
	if (!old_pwd)
		return (1);
	target = get_target_dir(args, *env_list);
	if (!target)
	{
		free (old_pwd);
		return (1);
	}
	return (cd_execute(target, old_pwd, env_list, args));
}
