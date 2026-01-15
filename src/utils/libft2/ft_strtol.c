/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 09:34:53 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/05 10:27:58 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_parse_digits(const char *ptr, char **endptr)
{
	long	result;

	result = 0;
	while (ft_isdigit(*ptr))
	{
		result = result * 10 + (*ptr - '0');
		ptr++;
	}
	if (endptr)
		*endptr = (char *)ptr;
	return (result);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	long		result;
	int			sign;
	const char	*ptr;

	if (base != 10)
	{
		if (endptr)
			*endptr = (char *)nptr;
		return (0);
	}
	ptr = nptr;
	result = 0;
	sign = 1;
	while (ft_isspace(*ptr))
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	result = ft_parse_digits(ptr, endptr);
	return (result * sign);
}
