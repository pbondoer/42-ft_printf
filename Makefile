# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 21:02:30 by pbondoer          #+#    #+#              #
#    Updated: 2017/02/08 07:11:20 by pbondoer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include libprintf.mk

# directories
SRC_DIR  := ./src
INC_DIR  := ./includes
OBJ_DIR  := ./obj
TEST_DIR := ./test

# src / obj files
SRC		:= check.c \
		   format.c \
		   atoi.c

OBJ		:= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# compiler
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -O3 -march=native -pipe

# libraries
L_FT	:= ../libft
include $(L_FT)/libft.mk

# rules
all: $(OBJ_DIR) $(PRINTF_NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LIB_INC) -o $@ -c $<

$(PRINTF_NAME): $(OBJ)
	ar rc $(PRINTF_NAME) $(OBJ)
	ranlib $(PRINTF_NAME)

test:
	@$(MAKE) -C $(TEST_DIR) --no-print-directory

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(PRINTF_NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re relibs test
