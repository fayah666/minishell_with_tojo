/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 03:25:49 by hfandres          #+#    #+#             */
/*   Updated: 2025/12/10 11:08:45 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char *ft_strndup(const char *s, int n)
{
	char *dup;

	dup = malloc((n + 1) * sizeof(char));
	if (!dup)
		return NULL;
	ft_strlcpy(dup, s, n + 1);
	return (dup);
}

