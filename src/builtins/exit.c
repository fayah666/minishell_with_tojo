/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:02:42 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/18 09:59:41 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
/*
** Checks if a string represents a valid number (allowing optional sign).
*/
static int	is_numeric_string(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

int	check_limits(const char *str, char sign)
{
	int			len;
	const char	*limit;
	const char	*num;

	limit = "9223372036854775807";
	num = str;
	if (*num == '+' || *num == '-')
		num++;
	len = 0;
	len = ft_strlen(num);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (sign == '-')
		limit = "9223372036854775808";
	if (ft_strcmp(num, limit) > 0)
		return (1);
	return (0);
}

void	ft_exit(char **args, t_all *all)
{
	int	exit_code;

	exit_code = all->exit_code;
	if (args[1])
	{
		if (!is_numeric_string(args[1]) || \
check_limits(args[1], args[1][0]))
		{
			printf("exit\n");
			exec_error("exit", "numeric argument required");
			exit(2);
		}
		if (args[2])
		{
			exec_error("exit", "too many arguments");
			all->exit_code = 1;
			return ;
		}
		exit_code = ft_atoll(args[1]);
	}
	printf("exit\n");
	exit(exit_code % 256);
}
