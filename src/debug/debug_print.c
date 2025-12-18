/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:09:45 by torakoto          #+#    #+#             */
/*   Updated: 2025/11/27 08:24:42 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints the redirections for a single command.
*/
static void	print_redirections(t_redir *redir_list)
{
	t_redir	*temp_redir;

	temp_redir = redir_list;
	while (temp_redir)
	{
		printf("  Redir: type %s, file [%s]\n",
			token_type_to_str(temp_redir->type), temp_redir->filename);
		temp_redir = temp_redir->next;
	}
}

/*
** Prints the arguments for a single command.
*/
static void	print_arguments(char **args)
{
	int	j;

	j = 0;
	if (args)
	{
		while (args[j])
		{
			printf("  Arg %d: [%s]\n", j, args[j]);
			j++;
		}
	}
}

/*
** Prints the entire command table for debugging purposes.
** This is the only non-static function, called from main.c.
*/
void	print_cmd_table(t_cmd *cmd_table)
{
	t_cmd	*temp_cmd;
	int		i;

	printf("--- Command Table ---\n");
	temp_cmd = cmd_table;
	i = 0;
	while (temp_cmd)
	{
		printf("Command #%d:\n", ++i);
		print_redirections(temp_cmd->redirections);
		print_arguments(temp_cmd->args);
		temp_cmd = temp_cmd->next;
	}
	printf("---------------------\n");
}

void	test_path_finder(t_cmd *cmd_table, t_all *all)
{
	char	*cmd_path;

	if (cmd_table && cmd_table->args && cmd_table->args[0])
	{
		cmd_path = find_command_path(cmd_table->args[0], all->env_list);
		if (cmd_path)
		{
			printf("Found command path: %s\n", cmd_path);
			free(cmd_path);
		}
		else
			printf("Command not found: %s\n", cmd_table->args[0]);
	}
}
