# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 13:48:51 by torakoto          #+#    #+#              #
#    Updated: 2026/01/15 12:15:21 by hfandres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -I includes -I libft
LDFLAGS_READLINE = -lreadline

SRC_DIR = src
OBJ_DIR = obj

SRCS =	$(SRC_DIR)/main.c \
        $(SRC_DIR)/env/env_init.c \
        $(SRC_DIR)/env/env_vars.c \
        $(SRC_DIR)/env/env_parse.c \
        $(SRC_DIR)/exec/path.c \
        $(SRC_DIR)/exec/executor_main.c \
        $(SRC_DIR)/exec/executor_helpers.c \
        $(SRC_DIR)/exec/executor_child.c \
        $(SRC_DIR)/exec/error.c \
        $(SRC_DIR)/exec/env_array.c \
        $(SRC_DIR)/pipeline/pipeline.c \
        $(SRC_DIR)/redir/redirect.c \
        $(SRC_DIR)/signals/signals.c \
        $(SRC_DIR)/signals/signals_heredoc.c \
        $(SRC_DIR)/parsing/lexer.c \
        $(SRC_DIR)/parsing/expander.c \
        $(SRC_DIR)/parsing/expander_content.c \
        $(SRC_DIR)/parsing/parser.c \
        $(SRC_DIR)/parsing/parser_args.c \
        $(SRC_DIR)/parsing/parser_free.c \
        $(SRC_DIR)/parsing/parser_heredoc.c \
		$(SRC_DIR)/parsing/heredoc_expand.c \
        $(SRC_DIR)/builtins/builtins.c \
        $(SRC_DIR)/builtins/echo.c \
        $(SRC_DIR)/builtins/pwd.c \
        $(SRC_DIR)/builtins/env.c \
        $(SRC_DIR)/builtins/exit.c \
        $(SRC_DIR)/builtins/cd.c \
        $(SRC_DIR)/builtins/export.c \
        $(SRC_DIR)/builtins/export_split.c \
        $(SRC_DIR)/builtins/unset.c \
		$(SRC_DIR)/utils/env/env_utils.c \
        $(SRC_DIR)/utils/libft2/ft_strcmp.c \
        $(SRC_DIR)/utils/libft2/ft_strndup.c \
        $(SRC_DIR)/utils/libft2/ft_strtol.c \
        $(SRC_DIR)/utils/libft2/ft_atoll.c \
        $(SRC_DIR)/utils/exec/exec_utils.c \
        $(SRC_DIR)/utils/pipeline/pipeline_utils.c \
        $(SRC_DIR)/utils/redir/redirect_utils.c \
        $(SRC_DIR)/utils/libft2/is_whitespace_only.c \
        $(SRC_DIR)/utils/colors.c \
        $(SRC_DIR)/utils/parsing/token_utils.c \
        $(SRC_DIR)/utils/parsing/expander_utils.c \
        $(SRC_DIR)/utils/parsing/parser_utils.c \
        $(SRC_DIR)/utils/parsing/parser_heredoc_utils.c \
        $(SRC_DIR)/utils/builtins/export_utils.c \
        $(SRC_DIR)/utils/builtins/builtins_utils.c \

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
	rm -f rl.supp
	rm -rf $(OBJ_DIR)

fclean:	clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

valgo: rlsupp
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=rl.supp ./$(NAME)

rlsupp :
	@echo "{" > rl.supp
	@echo "	ignore_readlines_errors" >> rl.supp
	@echo "	Memcheck:Leak" >> rl.supp
	@echo "	..." >> rl.supp
	@echo "	obj:*/libreadline.so.*" >> rl.supp
	@echo "}" >> rl.supp

.PHONY: all clean fclean re valgo rlsupp
