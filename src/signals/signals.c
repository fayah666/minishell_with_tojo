/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:20:32 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/18 10:58:03 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>

/**
 * @brief Sets up signal handlers for the interactive prompt.
 * - SIGINT (Ctrl+C) is caught to redisplay the prompt.
 * - SIGQUIT (Ctrl+\) is ignored.
 */
void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = interactive_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * @brief The handler for signals during command execution.
 * It prints a newline to keep the prompt clean after a child process
 * is terminated by a signal.
 */
static void	exec_signal_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * @brief Sets up signal handlers for the parent process during execution.
 * - SIGINT (Ctrl+C) is caught to print a newline.
 * - SIGQUIT (Ctrl+\) is caught to print a newline.
 * The parent process itself does not terminate.
 */
void	setup_exec_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = exec_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Resets signal handlers to their default behavior for child processes.
 * This allows SIGINT and SIGQUIT to terminate the child process as expected.
 */
void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
