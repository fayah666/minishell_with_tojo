/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 10:59:31 by hfandres          #+#    #+#             */
/*   Updated: 2026/01/09 15:15:51 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_status(int new_status)
{
	static int	status = 0;

	if (new_status != -1)
		status = new_status;
	return (status);
}

static void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

static void	signal_quit_heredoc(int signo)
{
	(void)signo;
	signal_status(1);
}

void	set_heredoc_sig(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_quit_heredoc;
	sigaction(SIGINT, &act, NULL);
}

int	check_variable_hook(void)
{
	if (signal_status(-1) == 1)
		rl_done = 1;
	return (0);
}
