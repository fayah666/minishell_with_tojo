/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:43:35 by hfandres          #+#    #+#             */
/*   Updated: 2025/03/15 13:15:10 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_words(const char *s, const char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static int	ft_check_mem(char **split, int i)
{
	if (!split[i])
	{
		while (i >= 0)
		{
			free(split[i]);
			i--;
		}
		return (0);
	}
	return (1);
}

static void	ft_fill_array(char **split, const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s)
			{
				count++;
				s++;
			}
			split[i] = ft_substr(s - count, 0, count);
			if (!ft_check_mem(split, i))
				return ;
			count = 0;
			i++;
		}
		else
			s++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		w_count;

	w_count = ft_count_words(s, c);
	split = malloc (sizeof(char *) * (w_count + 1));
	if (!split)
		return (NULL);
	split[w_count] = NULL;
	ft_fill_array(split, s, c);
	return (split);
}
