/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:58:51 by hfandres          #+#    #+#             */
/*   Updated: 2025/03/14 12:56:48 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_isset(const char s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_countset(char const *s1, char const *set)
{
	int	count;

	count = 0;
	while (s1[count] && ft_isset(s1[count], set))
		count++;
	return (count);
}

static int	ft_countrset(const char *s1, const char *set)
{
	int	count;

	count = ft_strlen(s1);
	while (count && ft_isset(s1[count - 1], set))
		count--;
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		first;
	int		last;

	first = ft_countset(s1, set);
	last = ft_countrset(s1, set);
	trim = ft_substr(s1, first, last - first);
	return (trim);
}
