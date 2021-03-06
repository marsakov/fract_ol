#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 20:42:29 by msakovyc          #+#    #+#              #
#    Updated: 2018/05/22 20:42:30 by msakovyc         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol
SRCS = main.c fractals.c
FLAGS = -Wall -Werror -Wextra

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(SRCS)
	@ make -C libft re
	@ gcc $(FLAGS) -lmlx -lm -framework OpenGL -framework AppKit $(SRCS) libft/libft.a -o $(NAME)

%.o:%.c
	@ gcc -o $@ -c $< -I ./libft/

clean:
	@ make -C libft clean

fclean: clean
	@ rm -f $(NAME)
	@ make -C libft fclean

re: fclean all
