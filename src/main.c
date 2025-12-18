/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:01:29 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/18 08:50:43 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_bool g_ctrlc_received = FALSE;

void	interactive_sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_ctrlc_received = TRUE;
}

static void	process_input(char *input, t_all *all)
{
	t_cmd	*cmd_table;

	if (has_unclosed_quotes(input))
	{
		printf("minishell: syntax error: unclosed quotes\n");
		all->exit_code = 2;
		return ;
	}
	all->tokens = lexer(input);
	expander(all);
	cmd_table = parser(all);
	executor(cmd_table, all);
	free_cmd_table(cmd_table);
	free_token_list(all->tokens);
	all->tokens = NULL;
}

static void	run_prompt_loop(t_all *all)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (g_ctrlc_received)
		{
			g_ctrlc_received = FALSE;
			all->exit_code = 130;
		}
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (!is_whitespace_only(input))
		{
			add_history(input);
			process_input(input, all);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_all	all;

	(void)ac;
	(void)av;
	all.exit_code = 0;
	all.tokens = NULL;
	all.heredoc_interrupted = 0;
	setup_interactive_signals();
	all.env_list = init_env(envp);
	run_prompt_loop(&all);
	free_env_list(all.env_list);
	return (all.exit_code);
}
