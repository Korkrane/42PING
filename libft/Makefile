# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 14:40:58 by bahaas            #+#    #+#              #
#    Updated: 2022/06/18 04:04:07 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.phony: all clean fclean re bonus

NAME		= libft.a

CC		= clang

CFLAGS		= -Wall -Wextra -Werror

HEADER		= -I. -c

SRCS = $(wildcard *.c)\
		$(wildcard boolean/*.c)\
		$(wildcard error/*.c)\
		$(wildcard gnl/*.c)\
		$(wildcard ints/*.c)\
		$(wildcard lists/*.c)\
		$(wildcard memory/*.c)\
		$(wildcard misc/*.c)\
		$(wildcard put/*.c)\
		$(wildcard strings/*.c)\

OBJS		= ${SRCS:.c=.o}

.c.o:
			@printf "\033[34m[LIBFT]\033[0m Generating libft objects files: \033[0;33m%-33.33s\r\033[0m" $@
			@${CC} ${CFLAGS} ${HEADER} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}

			@ar rc ${NAME} ${OBJS}
			@echo "\n\033[34m[LIBFT]\033[0m \033[32mLIBRARY READY\033[0m"
			@ranlib ${NAME}

clean:
			@rm -f ${OBJS}
			@echo "\033[34m[LIBFT]\033[0m \033[32mDelete object files :OK\033[0m"

fclean:		clean
			@rm -f ${NAME}
			@echo "\033[34m[LIBFT]\033[0m \033[32mDelete executable files : \033[32mOK\033[0m"

re:			fclean	all
