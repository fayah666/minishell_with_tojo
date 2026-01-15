/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace_only.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:47:05 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/22 21:50:03 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(unsigned int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_whitespace_only(const char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!(ft_isspace((unsigned char)*str)))
			return (0);
		str++;
	}
	return (1);
}
