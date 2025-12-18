/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace_only.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torakoto <torakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:47:05 by torakoto          #+#    #+#             */
/*   Updated: 2025/11/25 11:52:29 by torakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace_only(const char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!(isspace((unsigned char)*str)))
			return (0);
		str++;
	}
	return (1);
}
