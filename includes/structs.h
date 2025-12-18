/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:24:27 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/18 10:57:24 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <signal.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

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

// Struct to hold general expansion state
typedef struct s_exp_state
{
	int				i;
	char			quote_char;
}					t_exp_state;

// Struct to hold heredoc expansion state
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
	int				exit_code;
	int				heredoc_interrupted;
}					t_all;

typedef struct s_hdoc_data
{
	int				pipefd[2];
	char			*delimiter;
	sigset_t		mask;
	sigset_t		oldmask;
}					t_hdoc_data;

#endif
