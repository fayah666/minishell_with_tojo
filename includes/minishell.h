/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:58:17 by torakoto          #+#    #+#             */
/*   Updated: 2025/12/18 10:54:58 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include "libft.h"

// --- Signal Prototypes ---
void		setup_interactive_signals(void);
void		setup_exec_signals(void);
void		setup_child_signals(void);
void	interactive_sigint_handler(int signum);
// --- Environment Prototypes ---
t_env		*new_env_node(char *key, char *value);
void		env_add_back(t_env **head, t_env *new_node);
t_env		*init_env(char **envp);
// env_utils.c
void		free_env_list(t_env *head);
t_env		*find_env_var(t_env *head, const char *key);
void		create_minimal_env(t_env **env_list);
void		update_shell_level(t_env **env_list);

// Environment variable manipulation
int			is_valid_identifier(char *str);
void		set_env_var(t_env **env_list, char *key, char *value);
void		unset_env_var(t_env **env_list, char *key);

// utils
int			is_whitespace_only(const char *str);
char 		*ft_strndup(const char *s, int n);
int			ft_strcmp(const char *s1, const char *s2);
// lexing
t_token		*lexer(const char *input);
t_token		*new_token(char *content, t_type type);
void		add_token_back(t_token **list, t_token *new);
void		free_token_list(t_token *head);
const char	*token_type_to_str(t_type type);

// quotes
int			has_unclosed_quotes(const char *input);

// expander
int			expander(t_all *all);

// expander_utils
char		*get_env_value(const char *key, t_env *env_list);
char		*append_char(char *str, char c);
char		*join_and_free(char *s1, char *s2);

// parser
t_cmd		*parser(t_all *all);
void		free_cmd_table(t_cmd *head);

// parser_utils
t_cmd		*new_cmd_node(void);
int			add_arg_to_cmd(t_cmd *cmd, char *arg);
int			is_redir(t_type type);
int			syntax_error(char *token_content, t_all *all);

// --- Parser Freeing ---
void		free_cmd_table(t_cmd *head);

// --- Debugging Prototypes ---
void		print_cmd_table(t_cmd *cmd_table);
void		test_path_finder(t_cmd *cmd_table, t_all *all);

// --- Path Resolution ---
char		*find_command_path(const char *cmd, t_env *env_list);

// --- Execution ---
void		executor(t_cmd *cmd_table, t_all *all);
void		child_process(t_cmd *cmd, t_all *all);
char		**env_list_to_array(t_env *env_list);
void		free_array(char **arr);
void		exec_error(char *cmd, char *msg);

// --- Execution Utilities ---
void		handle_path_error(char *cmd_str, t_all *all);
void		apply_heredoc_redirections(t_cmd *cmd);
void		close_heredoc_fds(t_cmd *cmd);
int			apply_redirections(t_cmd *cmd);
void		save_std_fds(int saved_fds[2]);
void		restore_std_fds(int saved_fds[2]);

// --- Pipeline ---
int			execute_pipeline(t_cmd *cmd_list, t_all *all);
int			pipeline_fork_child(t_cmd *cmd, t_all *all, int in_fd,
				int pipe_fds[2]);
void		wait_for_children(pid_t last_pid, t_all *all);
void		pipeline_child(t_cmd *cmd, t_all *all, int in_fd, int pipe_fds[2]);
void		parent_pipeline_step(t_cmd *current, int *in_fd, int pipe_fds[2]);
void		handle_child_status(int status, t_all *all);

// --- Here-documents ---
int			handle_heredocs(t_cmd *cmd_list, t_all *all);
int			has_heredocs(t_cmd *cmd_list);
char		*remove_quotes(char *str);

// --- Heredoc Utilities ---
void		setup_heredoc_signals(void);
int			init_heredoc_data(t_hdoc_data *data, t_redir *redir);
void		cleanup_heredoc_data(t_hdoc_data *data, int close_pipes);
void		heredoc_child_process(t_hdoc_data *data, t_redir *redir,
				t_all *all);
int			heredoc_parent_process(pid_t pid, t_hdoc_data *data, t_redir *redir,
				t_all *all);
char		*expand_heredoc_line(char *line, t_all *all);

#endif
