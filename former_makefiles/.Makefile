# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 11:57:11 by simarcha          #+#    #+#              #
#    Updated: 2024/06/06 12:33:44 by simarcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra
NAME				= minishell
RM					= rm -rf

#FILES AND PATHS
#HEADER - Where the includes files are located
INCLUDE_DIR			= inc/
INCLUDE_FILES		= minishell.h \
					  libft.h
INCLUDE				= $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))
INCLUDE_FLAGS       = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#SRCS - Where the main files for this project are located
SRCS_DIR			=	src/
SRCS_FILES			= 	main.c \
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
    					expander/manage_quotes.c \
					    expander/calculate_len_for_malloc.c \
 						expander/expand_the_line.c \
 					   	expander/check_before_expansion.c \
   						expander/word_splitting.c \
    					expander/utils_expander.c \
					    errors/parser_errors.c \
 						builtins/builtin_echo.c \
  						builtins/builtin_pwd.c \
    					builtins/builtin_env.c \
    					builtins/builtin_exit.c \
    					builtins/builtin_utils_nodes.c \
    					builtins/builtin_export.c \
    					builtins/builtin_export_helper.c \
    					builtins/builtin_unset.c \
    					builtins/builtin_cd.c \
    					utils/signals.c		
SRCS				= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJ_SRCS			= $(SRCS:.c=.o)

#READLINE
READLINE_DIR 		= ./readline-8.1
READLINE_LIB 		= -lreadline -lhistory -L $(READLINE_DIR)

#LIBFT
LIBFT_DIR			= libft/
LIBFT_ARCHIVE		= $(addprefix $(LIBFT_DIR), libft.a)
LIBFT_LIB			= -L$(LIBFT_DIR) -lft

#RULES AND COMMANDS
all:				$(LIBFT_ARCHIVE) $(NAME)

%.o:				%.c Makefile $(INCLUDE)
					@$(CC) $(CFLAGS) $(INCLUDE_FLAGS)-c $< -o $@

$(NAME):			$(OBJ_SRCS) $(LIBFT_ARCHIVE) Makefile
					$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(OBJ_SRCS) $(LIBFT_LIB) $(READLINE_LIB) -o $(NAME)

$(LIBFT_ARCHIVE):
					@$(MAKE) -s -C $(LIBFT_DIR)
					@echo "\033[1;32m\033[1mAll Libft files compiled in $(LIBFT_DIR).\033[0m"

clean:
				    @echo "\033[1;31m\033[1mDeleting every object files\033[0m" 
					@echo "\033[1mCleaning the object srcs files\033[0m"
					$(RM) $(OBJ_SRCS)
					@echo ""
					@echo "\033[1mCleaning the object libft files\033[0m"
					@$(MAKE) clean -C $(LIBFT_DIR)

fclean:				clean
				    @echo "\033[1;31m\033[1mDeleting the executable and archive files\033[0m" 
					$(RM) $(NAME)
					@echo ""
					@echo "\033[1;31m\033[1mCleaning the libft object and archive files\033[0m"
					$(MAKE) fclean -C $(LIBFT_DIR)

re:					fclean all

.PHONY:				all clean fclean re