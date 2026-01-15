/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:20:00 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/22 21:20:00 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

static char	**realloc_args(char **old_args, int count, char *new_arg)
{
	char	**new_args;
	int		i;

	new_args = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (old_args && old_args[i])
	{
		new_args[i] = old_args[i];
		i++;
	}
	new_args[i] = ft_strdup(new_arg);
	if (!new_args[i])
	{
		free(new_args);
		return (NULL);
	}
	new_args[i + 1] = NULL;
	return (new_args);
}

int	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_args;

	count = count_args(cmd->args);
	new_args = realloc_args(cmd->args, count, arg);
	if (!new_args)
		return (1);
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	return (0);
}
