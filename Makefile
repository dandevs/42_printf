# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/12/10 20:31:14 by danimend          #+#    #+#             #
#    Updated: 2025/12/10 20:38:02 by danimend         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Project name (library)
NAME = libftprintf.a
SRCS = ft_printf.c $(wildcard libft/*.c) $(wildcard utilities/*.c)
OBJS = $(SRCS:.c=.o)
INCLUDES = -I. -Ilibft -Iutilities

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re