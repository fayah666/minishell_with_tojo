/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:29:13 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/10 10:38:31 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_error(char *cmd, char *msg)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", ft_strlen(": "));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", ft_strlen("\n"));
}
