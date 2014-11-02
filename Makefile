# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/20 23:02:19 by mdiouf            #+#    #+#              #
#    Updated: 2014/11/01 16:42:39 by mdiouf           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell1

SRCS = buildin.c \
		cpy_vars.c \
		excve.c \
		fork.c \
		get_next_line.c \
		main.c \
		cd.c \
		space_mnp.c \
		split_args.c \
		split_paths.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

.PHONY: all, clean, fclean, re

all: $(NAME)

make:
	make -C libft/

$(NAME): $(OBJS)
	gcc -o $(NAME) $(OBJS) -L libft/ -lft -g

%.o : %.c
	make -C libft/
	gcc -I libft/includes/ $(FLAGS) -c $^ -g

clean:
	make -C libft/ clean
	/bin/rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all
