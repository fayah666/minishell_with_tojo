/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:57:36 by hfandres          #+#    #+#             */
/*   Updated: 2025/03/12 13:48:35 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	i = -1;
	s_len = ft_strlen(s);
	if ((int)s_len < (int)start)
		return (ft_strdup(""));
	if (s_len <= len)
		len = s_len - start;
	sub = (char *)malloc(sizeof (char) * (len + 1));
	if (!sub)
		return (NULL);
	while (++i < len)
		sub[i] = s[start + i];
	sub[len] = '\0';
	return (sub);
}
