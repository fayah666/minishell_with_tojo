/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:09:28 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 12:47:30 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static char	*get_target_dir(char **args, t_env *env_list)
{
	t_env	*var;

	if (!args[1])
	{
		var = find_env_var(env_list, "HOME");
		if (!var)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			return (NULL);
		}
		return (var->value);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		var = find_env_var(env_list, "OLDPWD");
		if (!var)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 31);
			return (NULL);
		}
		return (var->value);
	}
	return (args[1]);
}

static void	update_pwd_vars(t_env **env_list, char *old_pwd)
{
	char	cwd[1024];

	if (old_pwd)
		set_env_var(env_list, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_var(env_list, "PWD", cwd);
}

static char	*update_old_pwd(t_env **env_list)
{
	char	*old_pwd;
	t_env	*pwd_var;
	char	cwd[1024];

	pwd_var = find_env_var(*env_list, "PWD");
	if (pwd_var)
		old_pwd = ft_strdup(pwd_var->value);
	else if (getcwd(cwd, sizeof(cwd)))
		old_pwd = ft_strdup(cwd);
	else
		old_pwd = ft_strdup("");
	return (old_pwd);
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
	target = get_target_dir(args, *env_list);
	if (!target)
		return (1);
	if (chdir(target) != 0)
	{
		write(2, "minishell: cd: ", 15);
		perror(target);
		return (1);
	}
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		printf("%s\n", target);
	update_pwd_vars(env_list, old_pwd);
	free (old_pwd);
	return (0);
}
