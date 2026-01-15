/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:33:16 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/10 10:33:30 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**skip_whitespace_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (NULL);
	while (args[i] && is_whitespace_only(args[i]))
		i++;
	return (&args[i]);
}

int	handle_redirections_with_fds(t_cmd *cmd, int *saved_fds, t_all *all)
{
	save_std_fds(saved_fds);
	if (apply_redirections(cmd) != 0)
	{
		all->exit_code = EXIT_GENERAL_ERROR;
		restore_std_fds(saved_fds);
		return (1);
	}
	return (0);
}

void	launch_child_process(t_cmd *cmd, t_all *all)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		exec_error("fork failed", NULL);
		all->exit_code = EXIT_GENERAL_ERROR;
		setup_interactive_signals();
		return ;
	}
	if (pid == 0)
	{
		setup_child_signals();
		child_process(cmd, all);
	}
	close_heredoc_fds(cmd);
	parent_process(pid, all);
	setup_interactive_signals();
}
