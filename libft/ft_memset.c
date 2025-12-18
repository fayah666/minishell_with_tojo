/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:58:41 by hfandres          #+#    #+#             */
/*   Updated: 2025/03/14 13:00:00 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n )
{
	unsigned char	*st;

	st = (unsigned char *)s;
	if (!s)
		return (NULL);
	while (n--)
		*(st++) = (unsigned char)c;
	return (s);
}
