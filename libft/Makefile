# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/17 13:18:59 by bahaas            #+#    #+#              #
#    Updated: 2021/05/27 20:35:48 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c \
				ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isdigit.c ft_isprint.c ft_itoa.c \
				ft_memccpy.c ft_memchr.c \
				ft_memcmp.c ft_memcpy.c ft_memmove.c \
				ft_memset.c ft_putchar_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c \
				ft_putstr_fd.c ft_split.c ft_strchr.c \
				ft_strdup.c ft_strjoin.c ft_strlcat.c \
				ft_strlcpy.c ft_strlen.c ft_strmapi.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c \
				ft_strtrim.c ft_substr.c ft_tolower.c \
				ft_toupper.c ft_atoi_base.c ft_free.c \
				ft_split_charset.c ft_strcmp.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
				ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c \
				ft_lstiter.c ft_lstmap.c \
				get_next_line.c get_next_line_utils.c ft_isnumb.c \
				ft_atoll.c ft_memalloc.c ft_strdel.c ft_strnew.c \
				ft_free_strs.c

CC			= clang
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
OBJS		= ${SRCS:.c=.o}

.c.o:
	@printf "\033[34m[LIBFT]\033[0m Generating libft .o files: \033[32mOK\033[0m%-33.33s\r"
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@ar rc ${NAME} ${OBJS}
			@ranlib ${NAME}
			@echo "\033[34m\n[LIBFT]\033[0m Building libft : \033[32mOK\033[0m"

all:		${NAME} | silent

clean:
			@${RM} ${OBJS} ${OBJS_BONUS} ${OBJS_GNL}
			@echo "\033[34m[LIBFT]\033[0m Delete .o files : \033[32mOK\033[0m"

fclean:		clean
			@${RM} ${NAME}
			@echo "\033[34m[LIBFT]\033[0m Delete .a file : \033[32mOK\033[0m"

re:			fclean all

.PHONY:		all clean fclean re silent
