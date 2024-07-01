# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 11:57:11 by simarcha          #+#    #+#              #
#    Updated: 2024/06/25 17:03:08 by anovio-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SETUP
CC                  = gcc
CFLAGS              = -Wall -Werror -Wextra -g -fsanitize=address
NAME                = minishell
RM                  = rm -rf

# Detect OS
UNAME_S := $(shell uname -s)

# Determine readline flags based on OS
ifeq ($(UNAME_S), Linux)
    READLINE_DIR        = ./readline-8.1
    READLINE_LIB        = -lreadline -lhistory -L$(READLINE_DIR)
    INCLUDE_FLAGS       = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(READLINE_DIR)
else ifeq ($(UNAME_S), Darwin)
    READLINE_DIR        = $(shell brew --prefix readline)
    READLINE_LIB        = -lreadline -lhistory -L$(READLINE_DIR)/lib
    INCLUDE_FLAGS       = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(READLINE_DIR)/include 
else
    $(error Unsupported OS: $(UNAME_S))
endif

# FILES AND PATHS

# INCLUDE - Where the header files are located

INCLUDE_DIR         =   includes/
INCLUDE_FILES       =   minishell.h \
                        libft.h
INCLUDE             =   $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))

SRCS_DIR            =   src/
SRCS_FILES          =   main.c \
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
                        executor/utils_executor_aux.c  \
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
                        builtins/cd_aux.c                 \
                        builtins/cleaning_builtin_nodes.c \
                        utils/signals.c                   \
                        utils/utils.c                     \
                        utils/utils_aux.c

OBJ_SRCS            =   $(addprefix $(SRCS_DIR), $(SRCS_FILES:.c=.o))

# LIBFT

LIBFT_DIR           =   libft/
LIBFT_SRCS          =   ft_memchr.c ft_memcmp.c ft_memmove.c ft_memset.c ft_strlcat.c \
                        ft_strlcpy.c ft_strlen.c ft_strtrim.c ft_atoi.c ft_atoi_base.c ft_memcpy.c \
                        ft_bzero.c ft_strmapi.c ft_calloc.c ft_strcmp.c ft_strcmp_simple.c ft_strncmp.c \
                        ft_isalnum.c ft_putchar_fd.c ft_strnstr.c ft_isalpha.c ft_putendl_fd.c ft_strrchr.c \
                        ft_isascii.c ft_putnbr_fd.c ft_isdigit.c ft_isspace.c ft_putstr_fd.c ft_substr.c \
                        ft_isprint.c ft_islower.c ft_isuper.c ft_split.c ft_tolower.c ft_itoa.c \
                        ft_strchr.c ft_toupper.c ft_strdup.c ft_striteri.c ft_strjoin.c \
                        ft_free_double_array.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
                        ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
                        ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 

LIBFT_OBJS          = $(addprefix $(LIBFT_DIR), $(LIBFT_SRCS:.c=.o))
LIBFT_ARCHIVE       = $(addprefix $(LIBFT_DIR), libft.a)
LIBFT_LIB           = -L$(LIBFT_DIR) -lft

# RULES AND COMMANDS

all:                $(LIBFT_ARCHIVE) $(NAME)

$(NAME):            $(OBJ_SRCS) $(LIBFT_ARCHIVE) ./Makefile includes/minishell.h includes/libft.h
					@$(CC) $(CFLAGS) $(OBJ_SRCS) $(INCLUDE_FLAGS) $(LIBFT_LIB) $(READLINE_LIB) -o $(NAME)
					@echo "\033[1;32m\033[1mSuccessfully built $(NAME).\033[0m"

$(LIBFT_ARCHIVE):   $(LIBFT_OBJS)
					@$(MAKE) -C $(LIBFT_DIR)
					@echo "\033[1;32m\033[1mAll Libft files compiled in $(LIBFT_DIR).\033[0m"

$(LIBFT_DIR)%.o:    $(LIBFT_DIR)%.c $(LIBFT_DIR)libft.h $(LIBFT_DIR)Makefile
					@echo "\033[1mCompiling $<...\033[0m"
					@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

%.o:                %.c $(INCLUDE)
					@echo "\033[1mCompiling $<...\033[0m"
					@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
					@echo "\033[1;31m\033[1mDeleting every object file\033[0m" 
					@echo "\033[1mCleaning the object src files\033[0m"
					@$(RM) $(OBJ_SRCS)
					@echo "\033[1mCleaning the object libft files\033[0m"
					@$(RM) $(LIBFT_OBJS)

fclean:             clean
					@echo "\033[1;31m\033[1mDeleting the executable file\033[0m" 
					$(RM) $(NAME)
					@echo "\033[1;31m\033[1mCleaning the libft executable file\033[0m"
					$(RM) $(LIBFT_ARCHIVE)

re:					fclean all

.PHONY:				all clean fclean re
