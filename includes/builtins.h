/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:35:02 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/24 16:56:18 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_env *env_list);

void	ft_exit(t_cmd *cmd, t_all *all);
int		ft_cd(char **args, t_env **env_list);
int		ft_export(char **args, t_env **env_list);
int		ft_unset(char **args, t_env **env_list);

void	print_sorted_env(t_env *env_list);
int		split_assignment(char *arg, char **key, char **value, char *operator);
char	*extract_key(char *arg, char *equals);
int		validate_and_set(char *key, char *value, t_env **env_list, char *arg);
int		dispatch_simple_builtin(char **args, t_all *all, int *builtin_status);
int		dispatch_complex_builtin(t_cmd *cmd, t_all *all);
int		dispatch_all_builtins(t_cmd *cmd, t_all *all, int *status);

int		is_builtin_command(const char *cmd);

char	*get_target_dir(char **args, t_env *env_list);
void	update_pwd_vars(t_env **env_list, char *old_pwd);
char	*update_old_pwd(t_env **env_list);
#endif
