/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:56:45 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/19 12:13:21 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>

static void	heredoc_child_loop(t_hdoc_data *data, t_redir *redir, t_all *all)
{
	char	*line;
	char	*to_write;

	while (1)
	{
		line = readline("> ");
		printf("DEBUG: ligne lue = |%s| del = %s\n", line, data->delimiter);
		if (!line || ft_strcmp(line, data->delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (redir->is_quoted)
			to_write = ft_strdup(line);
		else
			to_write = expand_heredoc_line(line, all);
		free(line);
		if (to_write)
		{
			write(data->pipefd[1], to_write, ft_strlen(to_write));
			write(data->pipefd[1], "\n", 1);
			free(to_write);
		}
	}
}

void	heredoc_child_process(t_hdoc_data *data, t_redir *redir, t_all *all)
{
	sigprocmask(SIG_SETMASK, &data->oldmask, NULL);
	close(data->pipefd[0]);
	setup_heredoc_signals();
	heredoc_child_loop(data, redir, all);
	free(data->delimiter);
	close(data->pipefd[1]);
	exit(0);
}

int	heredoc_parent_process(pid_t pid, t_hdoc_data *data, t_redir *redir,
		t_all *all)
{
	int			status;
	sigset_t	pending;

	close(data->pipefd[1]);
	free(data->delimiter);
	waitpid(pid, &status, 0);
	sigpending(&pending);
	if (sigismember(&pending, SIGINT))
	{
		signal(SIGINT, SIG_IGN);
		sigprocmask(SIG_UNBLOCK, &data->mask, NULL);
		setup_interactive_signals();
	}
	else
		sigprocmask(SIG_SETMASK, &data->oldmask, NULL);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(data->pipefd[0]);
		all->exit_code = 130;
		all->heredoc_interrupted = 1;
		return (1);
	}
	redir->heredoc_fd = data->pipefd[0];
	return (0);
}
