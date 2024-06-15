# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 11:57:11 by simarcha          #+#    #+#              #
#    Updated: 2024/06/15 17:28:24 by simarcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
CC                  = gcc
CFLAGS              = -Wall -Werror -Wextra -g #-g
NAME                = minishell
RM                  = rm -rf

#FILES AND PATHS
#INCLUDE - Where the header files are located
INCLUDE_DIR         = includes/
INCLUDE_FILES       = minishell.h \
                      libft.h
INCLUDE             = $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))
INCLUDE_FLAGS       = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)# -I$(READLINE_DIR)/include 

#SRCS - Where the main files for this project are located
SRCS_DIR            = src/
SRCS_FILES          = main.c \
                      lexer/tokenizer.c \
                      lexer/utils_lexer.c \
                      lexer/utils_nodes_lexer.c \
                      lexer/utils_nodes_aux.c \
                      parser/parser.c \
                      parser/redirections_parser.c \
                      parser/utils_parser.c \
                      parser/utils_nodes_parser.c \
                      executor/executor.c \
                      executor/hdoc.c \
                      executor/run_cmds.c \
                      executor/redirections.c \
                      executor/utils_executor.c \
                      utils/mini_live.c \
                      utils/verify_quotes.c \
                      expander/expander.c \
                      expander/variable_existence.c \
                      expander/calculate_len_for_malloc.c \
                      expander/expand_the_line.c \
                      expander/check_before_expansion.c \
                      expander/word_splitting.c \
                      expander/utils_expander.c \
                      expander/final_expansion_utils.c \
                      expander/final_expansion.c \
                      errors/parser_errors.c \
                      builtins/builtin_echo.c \
                      builtins/builtin_pwd.c \
                      builtins/builtin_env.c \
                      builtins/builtin_exit_utils.c \
                      builtins/builtin_exit.c \
                      builtins/builtin_utils_nodes.c \
                      builtins/builtin_export.c \
                      builtins/builtin_export_helper.c \
					  builtins/builtin_export_value_with_quotes.c \
                      builtins/builtin_unset.c \
                      builtins/builtin_cd.c \
                      builtins/cleaning_builtin_nodes.c \
                      utils/signals.c                   \
                      utils/utils.c
SRCS                = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJ_SRCS            = $(SRCS:.c=.o)

#READLINE
READLINE_DIR        = ./readline-8.1
READLINE_LIB        = -lreadline -lhistory -L$(READLINE_DIR)

#READLINE_DIR = $(shell brew --prefix readline)

#READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib

#LIBFT 
LIBFT_DIR           = libft/
LIBFT_ARCHIVE       = $(addprefix $(LIBFT_DIR), libft.a)
LIBFT_LIB           = -L$(LIBFT_DIR) -lft

#RULES AND COMMANDS
all:						$(LIBFT_ARCHIVE) $(NAME)

$(SRCS_DIR)%.o:				$(SRCS_DIR)%.c $(INCLUDE)
							@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(SRCS_DIR)lexer/%.o:		$(SRCS_DIR)lexer/%.c $(INCLUDE)
							@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(SRCS_DIR)parser/%.o:		$(SRCS_DIR)parser/%.c $(INCLUDE)
							@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(SRCS_DIR)executor/%.o:	$(SRCS_DIR)executor/%.c $(INCLUDE)
							@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(SRCS_DIR)utils/%.o:		$(SRCS_DIR)utils/%.c $(INCLUDE)
							@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(SRCS_DIR)expander/%.o:	$(SRCS_DIR)expander/%.c $(INCLUDE)
							@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(SRCS_DIR)errors/%.o:		$(SRCS_DIR)errors/%.c $(INCLUDE)
							@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(SRCS_DIR)builtins/%.o:	$(SRCS_DIR)builtins/%.c $(INCLUDE)
							@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(NAME):					$(OBJ_SRCS) $(LIBFT_ARCHIVE) Makefile
							@$(CC) $(CFLAGS) $(OBJ_SRCS) $(LIBFT_LIB) $(READLINE_LIB) -o $(NAME)
							@echo "\033[1;32m\033[1mSuccessfully built $(NAME).\033[0m"

$(LIBFT_ARCHIVE):
							@$(MAKE) -s -C $(LIBFT_DIR)
							@echo "\033[1;32m\033[1mAll Libft files compiled in $(LIBFT_DIR).\033[0m"
							
clean:
							@echo "\033[1;31m\033[1mDeleting every object file\033[0m" 
							@echo "\033[1mCleaning the object src files\033[0m"
							$(RM) $(OBJ_SRCS)
							@echo ""
							@echo "\033[1mCleaning the object libft files\033[0m"
							@$(MAKE) clean -C $(LIBFT_DIR)

fclean:						clean
							@echo "\033[1;31m\033[1mDeleting the executable and archive files\033[0m" 
							$(RM) $(NAME)
							@echo ""
							@echo "\033[1;31m\033[1mCleaning the libft object and archive files\033[0m"
							@$(MAKE) fclean -C $(LIBFT_DIR)

re:							fclean all

.PHONY:						all clean fclean re
