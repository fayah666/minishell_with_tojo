/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:35:02 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/08 13:35:56 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// --- Simple Built-ins ---
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_env *env_list);

// --- Complex Built-ins ---
void	ft_exit(char **args, t_all *all);
int		ft_cd(char **args, t_env **env_list);
int		ft_export(char **args, t_env **env_list);
int		ft_unset(char **args, t_env **env_list);

// --- Export Utilities ---
void	print_sorted_env(t_env *env_list);
int		split_assignment(char *arg, char **key, char **value);

// --- Dispatchers ---
int		dispatch_simple_builtin(char **args, t_all *all, int *builtin_status);
int		dispatch_complex_builtin(char **args, t_all *all);
int		dispatch_all_builtins(char **args, t_all *all, int *status);

#endif
