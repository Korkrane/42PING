# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 15:07:09 by bahaas            #+#    #+#              #
#    Updated: 2022/06/18 04:11:48 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_ping

SRCS			= $(wildcard srcs/*.c)\

CC				= clang

CFLAGS			= -Wextra -Werror -Wall -g

HEADER			= -I /includes

OBJS			= ${SRCS:.c=.o}

.c.o:
			@printf "\033[34m[FT_PING]\033[0m Generating ft_ping objects files: \033[0;33m%-33.33s\r\033[0m" $@
			@${CC} ${CFLAGS} ${HEADER} -c $< -o ${<:.c=.o}

all: 		${NAME}

ft_ping: 	${OBJS}
			@echo "\n\033[34m[FT_PING]\033[0m \033[32mGenerating ft_ping objects files: OK\033[0m"
			@make -C libft/ --no-print-directory -s
			@${CC} ${CFLAGS} ${HEADER} ${OBJS} -o ${NAME} -L libft/ -lft -lm
			@echo "\033[34m[FT_PING]\033[0m \033[32mPROGRAM READY\033[0m"

clean:
			@make clean -C libft/ --no-print-directory
			@rm -rf ${OBJS}
			@echo "\033[34m[FT_PING]\033[0m \033[32mDelete object files :OK\033[0m"

fclean:		clean
			@make fclean -C libft/ --no-print-directory
			@rm -rf ${NAME}
			@echo "\033[34m[FT_PING]\033[0m \033[32mDelete executable files : \033[32mOK\033[0m"

re: 		fclean all

.PHONY:	all clean fclean re
