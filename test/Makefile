# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/05 02:12:10 by pbondoer          #+#    #+#              #
#    Updated: 2017/02/08 02:35:18 by pbondoer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= test_printf

# directories
SRC_DIR	:= ./src
OBJ_DIR	:= ./obj
INC_DIR	:= ./includes
LIB_DIR	:= ../..

# src / obj files
SRC		:= main.c
OBJ		:= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# compiler and flags
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -O3 -march=native -pipe

# libraries
L_FT		:= $(LIB_DIR)/libft
L_PRINTF	:= $(LIB_DIR)/printf

include $(L_FT)/libft.mk
include $(L_PRINTF)/libprintf.mk

.PHONY: all clean fclean re relibs

all:
	mkdir -p $(OBJ_DIR)
	@$(MAKE) -C $(L_FT) --no-print-directory
	@$(MAKE) -C $(L_PRINTF) --no-print-directory
	@$(MAKE) $(NAME) --no-print-directory

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LIB_INC) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIB_LNK) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

relibs:
	@$(MAKE) -C $(L_FT) re --no-print-directory
	@$(MAKE) re --no-print-directory
