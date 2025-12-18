/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:53:33 by hfandres          #+#    #+#             */
/*   Updated: 2025/03/15 12:35:10 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*chr;

	chr = (unsigned char *)s;
	while (n--)
	{
		if ((unsigned char)c == *chr)
			return (chr);
		chr++;
	}
	return (NULL);
}
