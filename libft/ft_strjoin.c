/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:58:45 by hfandres          #+#    #+#             */
/*   Updated: 2025/04/18 12:32:03 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = malloc(sizeof (char) * len);
	i = -1;
	if (!join)
		return (NULL);
	while (++i < len)
	{
		if (i < ft_strlen(s1))
			join[i] = s1[i];
		else
		{
			join[i] = *s2;
			s2++;
		}
	}
	return (join);
}
