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

# Compiler and flags
CC = cc
CFLAGS = 

# Project name
NAME = ft_printf

# Source files - get all .c files recursively
SRCS = $(wildcard *.c) $(wildcard 42_libft/*.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Include directories
INCLUDES = -I. -I42_libft

# Default target
all: $(NAME)

# Link all object files
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything including executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Run the program after building
run: all
	./$(NAME)

.PHONY: all clean fclean re run
