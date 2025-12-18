/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:57:57 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/02 14:04:17 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

int	init_heredoc_data(t_hdoc_data *data, t_redir *redir)
{
	if (pipe(data->pipefd) == -1)
		return (perror("pipe"), 1);
	data->delimiter = remove_quotes(redir->filename);
	if (!data->delimiter)
	{
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		return (1);
	}
	sigemptyset(&data->mask);
	sigaddset(&data->mask, SIGINT);
	sigprocmask(SIG_BLOCK, &data->mask, &data->oldmask);
	return (0);
}

void	cleanup_heredoc_data(t_hdoc_data *data, int close_pipes)
{
	if (data->delimiter)
		free(data->delimiter);
	if (close_pipes)
	{
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
	sigprocmask(SIG_SETMASK, &data->oldmask, NULL);
}
