# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 16:45:08 by jaigonza          #+#    #+#              #
#    Updated: 2024/07/03 18:34:15 by jaigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Define variables
NAME = libftprintf.a
LIB = ar rcs
RM = rm -f
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DIR = .cache
# Source files
SRCS = printf/ft_printf.c \
       printf/ft_printf_render_int.c \
       printf/ft_printf_render_str.c \
       printf/ft_printf_utils.c

SRCS_BONUS = bonus/ft_printf_bonus.c \
             bonus/ft_printf_format_bonus.c \
             bonus/ft_printf_render_chars_bonus.c \
             bonus/ft_printf_render_num_bonus.c \
             bonus/ft_printf_utils_bonus.c \
             bonus/ft_printf_buf_bonus.c \
             bonus/ft_printf_render_num_utils_bonus.c

# Object files
OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)

# Default target
all: $(NAME)

# Rule for creating the library
$(NAME): $(OBJ)
	$(LIB) $(NAME) $(OBJ)

# Bonus target
bonus: $(DIR)
       
$(DIR): $(OBJ_BONUS) 
	$(LIB) $(NAME) $(OBJ_BONUS)
	touch $(DIR)

# Clean up object files
clean:
	$(RM) $(OBJ) $(OBJ_BONUS) $(DIR)

# Clean up object files and library
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Declare phony targets
.PHONY: all clean fclean re bonus

