# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/14 12:47:27 by miguel            #+#    #+#              #
#    Updated: 2021/08/24 17:57:37 by mmunoz-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

TIME = $(shell date +'%d/%m/%Y %H:%M:%S')
M =

NAME = philo

SRCS = main.c 			\
	philosophers.c		\
	init_simulation.c	\
	philo_utils.c		\
	plists/plists.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -pthreads

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

push: fclean
	git add ..
	git commit -m "$(TIME) - $M"
	git push origin master

.PHONY: all clean fclean re push
