NAME		= libft.a

HEADER 		= libft.h

SRCS		=	ft_memchr.c		\
				ft_memcmp.c		\
				ft_memmove.c	\
				ft_memset.c		\
				ft_strlcat.c	\
				ft_strlcpy.c	\
				ft_strlen.c		\
				ft_strtrim.c	\
				ft_atoi.c		\
				ft_atoi_base.c	\
				ft_memcpy.c		\
				ft_bzero.c		\
				ft_strmapi.c	\
				ft_calloc.c		\
				ft_strcmp.c		\
				ft_strcmp_simple.c	\
				ft_strncmp.c	\
				ft_isalnum.c	\
				ft_putchar_fd.c	\
				ft_strnstr.c	\
				ft_isalpha.c	\
				ft_putendl_fd.c	\
				ft_strrchr.c	\
				ft_isascii.c	\
				ft_putnbr_fd.c	\
				ft_isdigit.c	\
				ft_isspace.c	\
				ft_putstr_fd.c	\
				ft_substr.c		\
				ft_isprint.c	\
				ft_islower.c	\
				ft_isuper.c		\
				ft_split.c		\
				ft_tolower.c	\
				ft_itoa.c		\
				ft_strchr.c		\
				ft_toupper.c	\
				ft_strdup.c		\
				ft_striteri.c	\
				ft_strjoin.c	\
				ft_free_double_array.c \
				ft_lstnew_bonus.c		\
				ft_lstadd_front_bonus.c	\
				ft_lstsize_bonus.c		\
				ft_lstlast_bonus.c		\
				ft_lstadd_back_bonus.c	\
				ft_lstdelone_bonus.c	\
				ft_lstclear_bonus.c		\
				ft_lstiter_bonus.c		\
				ft_lstmap_bonus.c

OBJS	= 		$(SRCS:.c=.o)

LIB		=		ar -rcs
CC		= 		gcc
RM		= 		rm -f
CFLAGS	= 		-Wall -Wextra -Werror

all:			$(NAME)

$(NAME): 		$(OBJS)	Makefile $(HEADER)
				@$(LIB) $(NAME) $(OBJS)

# Depend. adicionales = solo se ejecutara la regla si cambia make o header
%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
