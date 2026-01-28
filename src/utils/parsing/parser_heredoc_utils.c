/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 10:57:16 by hfandres          #+#    #+#             */
/*   Updated: 2026/01/24 18:49:57 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static char	*build_temp_filename(int id, int counter)
{
	char	*pid_str;
	char	*count_str;
	char	*temp;
	char	*filename;

	pid_str = ft_itoa(id);
	if (!pid_str)
		return (NULL);
	count_str = ft_itoa(counter);
	if (!count_str)
		return (free(pid_str), NULL);
	temp = ft_strjoin(HEREDOC_PREFIX, pid_str);
	free(pid_str);
	if (!temp)
		return (free(count_str), NULL);
	filename = ft_strjoin(temp, "_");
	free(temp);
	if (!filename)
		return (free(count_str), NULL);
	temp = ft_strjoin(filename, count_str);
	free(filename);
	free(count_str);
	return (temp);
}

char	*create_unique_temp_file(int *out_fd)
{
	int			counter;
	char		*filename;
	int			fd;
	static int	id = 0;

	counter = 0;
	while (counter < 1000)
	{
		filename = build_temp_filename(id++, counter);
		if (!filename)
			return (NULL);
		fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd != -1)
		{
			*out_fd = fd;
			return (filename);
		}
		free(filename);
		if (errno != EEXIST)
			return (NULL);
		counter++;
	}
	return (NULL);
}

int	handle_heredoc_interruption(t_all *all)
{
	all->heredoc_interrupted = 1;
	signal_status(0);
	rl_done = 0;
	rl_event_hook = NULL;
	return (1);
}

int	handle_heredoc_eof(char *delimiter)
{
	signal_status(0);
	rl_done = 0;
	rl_event_hook = NULL;
	ft_putstr_fd ("warning: here-document delimited \
by end-of-file (wanted `", 2);
	ft_putstr_fd (delimiter, 2);
	ft_putstr_fd ("')\n", 2);
	return (0);
}
