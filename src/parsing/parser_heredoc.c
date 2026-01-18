/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 10:53:11 by hfandres          #+#    #+#             */
/*   Updated: 2026/01/18 15:19:47 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_temp_file(int *out_fd)
{
	char	*filename;

	filename = create_unique_temp_file(out_fd);
	if (!filename)
		return (NULL);
	return (filename);
}

static int	write_line_to_fd(int fd, char *line, int is_quoted, t_all *all)
{
	char	*to_write;

	if (is_quoted)
		to_write = ft_strdup(line);
	else
		to_write = expand_heredoc_line(line, all);
	if (!to_write)
		return (1);
	if (write(fd, to_write, ft_strlen(to_write)) == -1)
	{
		free(to_write);
		return (1);
	}
	if (write(fd, "\n", 1) == -1)
	{
		free(to_write);
		return (1);
	}
	free(to_write);
	return (0);
}

static int	read_heredoc_loop(int fd, t_redir *redir, \
t_all *all, char *delimiter)
{
	char	*line;

	rl_replace_line("", 0);
	rl_redisplay();
	while (1)
	{
		rl_event_hook = &check_variable_hook;
		if (signal_status(-1) == 1)
			return (handle_heredoc_interruption(all));
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (0);
		}
		if (write_line_to_fd(fd, line, redir->is_quoted, all) != 0)
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (handle_heredoc_eof(delimiter));
}

static int	process_single_heredoc(t_redir *redir, t_all *all, \
int id, char *delimiter)
{
	int		fd;

	(void)id;
	set_heredoc_sig();
	redir->temp_file = create_temp_file(&fd);
	if (!redir->temp_file)
	{
		free(delimiter);
		return (-1);
	}
	if (!read_heredoc_loop(fd, redir, all, delimiter))
		redir->heredoc_fd = open(redir->temp_file, O_RDONLY);
	close(fd);
	unlink(redir->temp_file);
	free(redir->temp_file);
	free(delimiter);
	return (redir->heredoc_fd);
}

int	parse_heredoc(t_cmd *cmd_list, t_all *all)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		id;
	char	*delimiter;

	id = 0;
	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == HERE_DOC)
			{
				delimiter = remove_quotes(redir->filename);
				if (!delimiter)
					return (1);
				if (process_single_heredoc(redir, all, id++, delimiter) < 0)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
