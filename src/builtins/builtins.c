/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:26:28 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:19:01 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

/*
** Checks if the command is a complex built-in and executes it.
** These must be run in the parent process for a single command.
** Returns 1 if it was a built-in, 0 otherwise.
*/
int	dispatch_complex_builtin(char **args, t_all *all)
{
    if (!args || !args[0])
        return (0);
    if (ft_strcmp(args[0], "cd") == 0)
        all->exit_code = ft_cd(args, &all->env_list);
    else if (ft_strcmp(args[0], "export") == 0)
        all->exit_code = ft_export(args, &all->env_list);
    else if (ft_strcmp(args[0], "unset") == 0)
        all->exit_code = ft_unset(args, &all->env_list);
    else if (ft_strcmp(args[0], "exit") == 0)
        ft_exit(args, all);
    else
        return (0);
    return (1);
}

/*
** Checks if the command is a simple built-in and executes it.
** Returns 1 if it was a built-in, 0 otherwise.
** The exit code of the built-in is returned via the `status` pointer.
*/
int	dispatch_simple_builtin(char **args, t_all *all, int *status)
{
    char	*cmd_name;

    if (!args || !args[0])
        return (0);
    cmd_name = args[0];
    if (ft_strcmp(cmd_name, "echo") == 0)
        *status = ft_echo(args);
    else if (ft_strcmp(cmd_name, "pwd") == 0)
        *status = ft_pwd();
    else if (ft_strcmp(cmd_name, "env") == 0)
        *status = ft_env(all->env_list);
    else
        return (0);
    return (1);
}

/*
** A unified dispatcher that checks for ANY builtin.
** This is used by child processes, especially in pipelines.
*/
int	dispatch_all_builtins(char **args, t_all *all, int *status)
{
    if (dispatch_simple_builtin(args, all, status))
        return (1);
    if (!args || !args[0])
        return (0);
    if (ft_strcmp(args[0], "cd") == 0)
        *status = ft_cd(args, &all->env_list);
    else if (ft_strcmp(args[0], "export") == 0)
        *status = ft_export(args, &all->env_list);
    else if (ft_strcmp(args[0], "unset") == 0)
        *status = ft_unset(args, &all->env_list);
    else if (ft_strcmp(args[0], "exit") == 0)
    {
        ft_exit(args, all);
        *status = all->exit_code;
    }
    else
        return (0);
    return (1);
}
