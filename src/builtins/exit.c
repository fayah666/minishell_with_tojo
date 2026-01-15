/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:02:42 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/15 10:41:12 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_string(const char *str)
{
	if (!str || !*str)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str && ft_isdigit(*str))
		str++;
	while (ft_isspace(*str))
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

int	check_len(int len)
{
	if (len > 19)
		return (1);
	return (0);
}

int	check_limits(const char *str)
{
	int			len;
	const char	*limit;
	const char	*num;
	char		sign;

	limit = "9223372036854775807";
	num = str;
	sign = '+';
	len = 0;
	while (ft_isspace(*num))
		num++;
	if (*num == '+' || *num == '-')
	{
		sign = *num;
		num++;
	}
	while (num[len] && num[len] != ' ')
		len++;
	if (check_len(len))
		return (1);
	if (sign == '-')
		limit = "9223372036854775808";
	if (ft_strncmp(num, limit, 19) > 0)
		return (1);
	return (0);
}

int	check_arguments(t_all *all, t_cmd *cmd)
{
	if (cmd && cmd->args && cmd->args[1])
	{
		if (!is_numeric_string(cmd->args[1]) || \
			check_limits(cmd->args[1]))
		{
			exec_error("exit", "numeric argument required");
			free_all_and_exit(all, 2);
		}
		if (cmd->args[2])
		{
			exec_error("exit", "too many arguments");
			all->exit_code = EXIT_GENERAL_ERROR;
			return (1);
		}
	}
	return (0);
}

void	ft_exit(t_cmd *cmd, t_all *all)
{
	int	exit_code;

	signal(SIGPIPE, SIG_IGN);
	exit_code = all->exit_code;
	if (cmd && cmd->args && cmd->args[1])
	{
		printf("exit\n");
		if (check_arguments(all, cmd))
		{
			signal(SIGPIPE, SIG_DFL);
			return ;
		}
		signal(SIGPIPE, SIG_DFL);
		free_all_and_exit(all, ft_atoll(cmd->args[1]) % 256);
	}
	if (!all->in_pipe)
		printf("exit\n");
	signal(SIGPIPE, SIG_DFL);
	free_all_and_exit(all, exit_code % 256);
}
