/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 01:37:26 by hfandres          #+#    #+#             */
/*   Updated: 2025/12/18 09:42:43 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_status(int status, t_all *all)
{
	if (WIFEXITED(status))
		all->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			all->exit_code = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			all->exit_code = 131;
		}
		else
			all->exit_code = 128 + WTERMSIG(status);
	}
}

void	wait_for_children(pid_t last_pid, t_all *all)
{
	int		status;
	pid_t	waited_pid;

	waited_pid = 0;
	while (waited_pid != -1)
	{
		waited_pid = wait(&status);
		if (waited_pid == last_pid)
			handle_child_status(status, all);
	}
}

void	pipeline_child(t_cmd *cmd, t_all *all, int in_fd, int pipe_fds[2])
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
			exec_error("dup2", "failed to redirect stdin");
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			exec_error("dup2", "failed to redirect stdout");
		close(pipe_fds[1]);
	}
	child_process(cmd, all);
}

void	parent_pipeline_step(t_cmd *current, int *in_fd, int pipe_fds[2])
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (current->next)
	{
		close(pipe_fds[1]);
		*in_fd = pipe_fds[0];
	}
}
