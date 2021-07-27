# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 15:07:09 by bahaas            #+#    #+#              #
#    Updated: 2021/07/27 17:50:29 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_ping

SRCS			= main.c

CC				= clang

#CFLAGS			= -Wextra -Werror -Wall -g
CFLAGS			= -g 

HEADER			= -I /includes

OBJS			= ${SRCS:.c=.o}

.c.o:
	@printf "\033[34m[FT_PING]\033[0m Generating .o files: \033[32mOK\033[0m%-33.33s\r\033[0m"
			@${CC} ${CFLAGS} ${HEADER} -c $< -o ${<:.c=.o}

all: 		${NAME}

ft_ping: 	${OBJS}
			@printf "\n"
			@make -C libft/ --no-print-directory -s
			@${CC} ${CFLAGS} ${HEADER} ${OBJS} -o ${NAME} -L libft/ -lft
			@echo "\033[34m[FT_PING]\033[0m Building ft_ping program : \033[32mOK\033[0m"

clean:
			@make clean -C libft/ --no-print-directory
			@rm -rf ${OBJS}
			@echo "\033[34m[FT_PING]\033[0m Delete .o files : \033[32mOK\033[0m"

fclean:		clean
			@make fclean -C libft/ --no-print-directory
			@rm -rf ${NAME}
			@echo "\033[34m[FT_PING]\033[0m Delete executable files : \033[32mOK\033[0m"

re: 		fclean all

.PHONY:	all clean fclean re
