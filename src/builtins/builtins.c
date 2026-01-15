/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:26:28 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/15 12:15:36 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	dispatch_complex_builtin(t_cmd *cmd, t_all *all)
{
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		all->exit_code = ft_cd(cmd->args, &all->env_list);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		all->exit_code = ft_export(cmd->args, &all->env_list);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		all->exit_code = ft_unset(cmd->args, &all->env_list);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd, all);
	else
		return (0);
	return (1);
}

int	dispatch_simple_builtin(char **args, t_all *all, int *builtin_status)
{
	char	*cmd_name;

	if (!args || !args[0])
		return (0);
	cmd_name = args[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		*builtin_status = ft_echo(args);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		*builtin_status = ft_pwd();
	else if (ft_strcmp(cmd_name, "env") == 0)
		*builtin_status = ft_env(all->env_list);
	else
		return (0);
	return (1);
}

int	dispatch_all_builtins(t_cmd *cmd, t_all *all, int *status)
{
	int	ret;

	ret = 1;
	if (!cmd->args || !cmd->args[0])
		ret = 0;
	if (dispatch_simple_builtin(cmd->args, all, status))
		ret = 1;
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		*status = ft_cd(cmd->args, &all->env_list);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		*status = ft_export(cmd->args, &all->env_list);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		*status = ft_unset(cmd->args, &all->env_list);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		ft_exit(cmd, all);
		*status = all->exit_code;
	}
	else
		ret = 0;
	return (ret);
}
