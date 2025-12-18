/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:32:22 by hfandres          #+#    #+#             */
/*   Updated: 2025/03/17 10:36:48 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	c;

	c = 0;
	if (n < 0)
		n *= -1;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		c++;
		n /= 10;
	}
	return (c);
}

static void	ft_revers(char *s)
{
	char	temp;
	int		len;
	int		i;

	len = ft_strlen(s);
	i = -1;
	while (++i < len / 2)
	{
		temp = *(s + len - (i + 1));
		*(s + len - (i + 1)) = *(s + i);
		*(s + i) = temp;
	}
}

static void	ft_fillstr(char *s, int n)
{
	if (n < 0)
	{
		n *= -1;
		s[0] = '-';
		s++;
	}
	if (n >= 10)
		ft_fillstr(s + 1, n / 10);
	n %= 10;
	*s = n + 48;
}

char	*ft_itoa(int n)
{
	int		nbrlen;
	char	*s;

	nbrlen = ft_nbrlen(n);
	if (n == -2147483648)
	{
		s = ft_strdup("-2147483648");
		return (s);
	}
	if (n < 0)
		nbrlen += 1;
	s = malloc((nbrlen + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[nbrlen] = '\0';
	ft_fillstr(s, n);
	if (n < 0)
		ft_revers(s + 1);
	else
		ft_revers(s);
	return (s);
}
