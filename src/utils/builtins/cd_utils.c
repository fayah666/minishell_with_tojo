/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:55:04 by hfandres          #+#    #+#             */
/*   Updated: 2026/01/24 16:55:45 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

char	*get_target_dir(char **args, t_env *env_list)
{
	t_env	*var;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
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

void	update_pwd_vars(t_env **env_list, char *old_pwd)
{
	char	cwd[1024];

	if (old_pwd)
		set_env_var(env_list, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_var(env_list, "PWD", cwd);
}

char	*update_old_pwd(t_env **env_list)
{
	char	*old_pwd;
	t_env	*pwd_var;

	pwd_var = find_env_var(*env_list, "PWD");
	if (pwd_var)
		old_pwd = ft_strdup(pwd_var->value);
	else
		old_pwd = ft_strdup("");
	return (old_pwd);
}
