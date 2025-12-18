# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 13:48:51 by torakoto          #+#    #+#              #
#    Updated: 2025/12/11 01:39:35 by hfandres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -I libft
LDFLAGS_READLINE = -lreadline

SRC_DIR = src
OBJ_DIR = obj

SRCS =	$(SRC_DIR)/main.c \
        $(SRC_DIR)/env/env_init.c \
        $(SRC_DIR)/env/env_utils.c \
        $(SRC_DIR)/env/env_vars.c \
        $(SRC_DIR)/utils/ft_strcmp.c \
        $(SRC_DIR)/utils/ft_strndup.c \
        $(SRC_DIR)/exec/path.c \
        $(SRC_DIR)/exec/executor.c \
        $(SRC_DIR)/exec/exec_utils.c \
        $(SRC_DIR)/exec/error.c \
        $(SRC_DIR)/exec/env_array.c \
        $(SRC_DIR)/exec/heredoc.c \
        $(SRC_DIR)/exec/heredoc_process.c \
        $(SRC_DIR)/exec/heredoc_utils.c \
        $(SRC_DIR)/exec/heredoc_expand.c \
        $(SRC_DIR)/pipeline/pipeline.c \
        $(SRC_DIR)/pipeline/pipeline_utils.c \
        $(SRC_DIR)/redir/redirect.c \
        $(SRC_DIR)/redir/redirect_utils.c \
        $(SRC_DIR)/utils/is_whitespace_only.c \
        $(SRC_DIR)/signals/signals.c \
        $(SRC_DIR)/parsing/lexer.c \
        $(SRC_DIR)/parsing/token_utils.c \
        $(SRC_DIR)/parsing/expander.c \
        $(SRC_DIR)/parsing/expander_utils.c \
        $(SRC_DIR)/parsing/parser.c \
        $(SRC_DIR)/parsing/parser_utils.c \
        $(SRC_DIR)/parsing/parser_free.c \
        $(SRC_DIR)/debug/debug_print.c \
        $(SRC_DIR)/builtins/builtins.c \
        $(SRC_DIR)/builtins/echo.c \
        $(SRC_DIR)/builtins/pwd.c \
        $(SRC_DIR)/builtins/env.c \
        $(SRC_DIR)/builtins/exit.c \
        $(SRC_DIR)/builtins/cd.c \
        $(SRC_DIR)/builtins/export.c \
        $(SRC_DIR)/builtins/export_utils.c \
        $(SRC_DIR)/builtins/export_split.c \
        $(SRC_DIR)/builtins/unset.c \

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LFT)
	$(CC) $(CFLAGS) $(OBJS) $(LFT) -o $(NAME) $(LDFLAGS_READLINE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LFT) :
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR)

fclean:	clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
