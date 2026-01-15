/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:15:29 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/13 09:39:08 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	ft_unset(char **args, t_env **env_list)
{
	int	i;

	if (!args || !args[0])
		return (1);
	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			unset_env_var(env_list, args[i]);
		i++;
	}
	return (0);
}
