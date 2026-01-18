/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:45:49 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/18 14:31:50 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline_fork_child(t_cmd *cmd, t_all *all, int in_fd, int pipe_fds[2])
{
	pid_t	pid;

	if (cmd->next)
	{
		if (pipe(pipe_fds) == -1)
		{
			exec_error("pipe", NULL);
			return (1);
		}
	}
	pid = fork();
	if (pid == -1)
	{
		exec_error("fork", NULL);
		if (cmd->next)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
		}
		return (-1);
	}
	if (pid == 0)
		pipeline_child(cmd, all, in_fd, pipe_fds);
	return (pid);
}

int	execute_pipeline(t_cmd *cmd_list, t_all *all)
{
	int		pipe_fds[2];
	int		in_fd;
	pid_t	pid;
	t_cmd	*current;

	in_fd = STDIN_FILENO;
	current = cmd_list;
	pid = -1;
	while (current)
	{
		pid = pipeline_fork_child(current, all, in_fd, pipe_fds);
		if (pid == -1)
			return (1);
		all->in_pipe = 1;
		parent_pipeline_step(current, &in_fd, pipe_fds);
		current = current->next;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	wait_for_children(pid, all);
	all->in_pipe = 0;
	return (0);
}
