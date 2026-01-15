/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:30:00 by hfandres          #+#    #+#             */
/*   Updated: 2026/01/13 10:24:14 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	colors_supported(void)
{
	char	*term;
	char	*colorterm;

	term = getenv("TERM");
	colorterm = getenv("COLORTERM");
	if (!term || !isatty(STDOUT_FILENO))
		return (0);
	if (colorterm && *colorterm)
		return (1);
	if (ft_strcmp(term, "xterm") == 0
		|| ft_strcmp(term, "xterm-256color") == 0
		|| ft_strcmp(term, "screen") == 0
		|| ft_strcmp(term, "linux") == 0
		|| ft_strcmp(term, "rxvt") == 0)
		return (1);
	return (0);
}

char	*get_colored_prompt(const char *msg, char *color)
{
	static char	prompt[256];

	if (colors_supported())
	{
		ft_strlcpy(prompt, color, sizeof(prompt));
		ft_strlcat(prompt, BOLD, sizeof(prompt));
		ft_strlcat(prompt, msg, sizeof(prompt));
		ft_strlcat(prompt, RESET, sizeof(prompt));
	}
	else
		ft_strlcpy(prompt, msg, sizeof(prompt));
	return (prompt);
}
