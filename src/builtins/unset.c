/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:15:29 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:38:31 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	ft_unset(char **args, t_env **env_list)
{
	int	i;
	int	status;

	if (!args || !args[0])
		return (1);
	status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(2, "minishell: unset: `", 19);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 26);
			status = 1;
		}
		else
			unset_env_var(env_list, args[i]);
		i++;
	}
	return (status);
}
