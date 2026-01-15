/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:24:27 by torakoto          #+#    #+#             */
/*   Updated: 2026/01/10 10:50:12 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <signal.h>

typedef enum e_exit_codes
{
	EXIT_SUCCESS = 0,
	EXIT_GENERAL_ERROR = 1,
	EXIT_SYNTAX_ERROR = 2,
	EXIT_COMMAND_NOT_FOUND = 127,
	EXIT_COMMAND_NOT_EXECUTABLE = 126,
	EXIT_SIGINT = 130,
	EXIT_SIGQUIT = 131
}					t_exit_code;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND
}					t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	int				has_quotes;
	struct s_token	*next;
}					t_token;

typedef struct s_exp_state
{
	int				i;
	char			quote_char;
}					t_exp_state;

typedef struct s_expand_state
{
	char			*line;
	char			*expanded;
	int				i;
	int				j;
}					t_expand_state;

typedef struct s_redir
{
	char			*filename;
	char			*temp_file;
	t_type			type;
	int				heredoc_fd;
	int				is_quoted;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_all
{
	t_env			*env_list;
	t_token			*tokens;
	t_cmd			*cmd_table;
	int				exit_code;
	int				heredoc_interrupted;
	int				in_pipe;
}					t_all;

#endif
