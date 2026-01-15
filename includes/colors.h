/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:30:00 by hfandres          #+#    #+#             */
/*   Updated: 2026/01/07 12:01:12 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define RESET		"\001\033[0m\002"
# define CYAN		"\001\033[36m\002"
# define BOLD		"\001\033[1m\002"

int		colors_supported(void);
char	*get_colored_prompt(const char *msg, char *color);

#endif
