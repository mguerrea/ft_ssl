# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/10 13:31:15 by mguerrea          #+#    #+#              #
#    Updated: 2020/07/10 14:36:10 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRC_DIR := ./srcs
OBJ_DIR := ./obj
INC_DIR := ./includes
SUB_DIRS := md5 ssl

LIB_FLAGS = -L./libft
LIBS = -lft
CC = clang
C_FLAGS = -Wall -Wextra -Werror

include $(SRC_DIR)/sources.mk
include $(INC_DIR)/includes.mk

SRC_SUB_DIRS = $(addprefix $(SRC_DIR)/,$(SUB_DIRS))
OBJ_SUB_DIRS = $(addprefix $(OBJ_DIR)/,$(SUB_DIRS))
INC_SUB_DIRS = $(addprefix $(INC_DIR)/,$(SUB_DIRS))

### MAIN AND SUB FILES ###
O_FILES = $(C_FILES:.c=.o)


### Full Paths ###
SRC = $(addprefix $(SRC_DIR)/,$(C_FILES))
OBJ = $(addprefix $(OBJ_DIR)/,$(O_FILES))
INC = $(addprefix $(INC_DIR)/,$(H_FILES))

FT_INC_DIR = libft/includes
INC_FLAGS = $(addprefix -I ,$(INC_DIR) $(INC_SUB_DIRS) $(FT_INC_DIR))

all: $(NAME)

libftmake:
	@make -C ./libft --no-print-directory

$(NAME): $(OBJ_DIR) $(OBJ) | libftmake
	@$(CC) -o $@ $(OBJ) $(LIB_FLAGS) $(LIBS)
	@echo "\n$(BLU)[$(NAME)]$(GRN) Compilation success$(RESET)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_SUB_DIRS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	$(CC) -c $< -o $@ $(INC_FLAGS) $(C_FLAGS)
	@echo "\r$(ERASE)$(BLU)[$(NAME)]$(RESET) $@ created\c"

clean:
	@/bin/rm -rf $(OBJ)
	@/bin/rm -rf $(OBJ_DIR)
	@make -C ./libft clean --no-print-directory
	@echo "$(BLU)[$(NAME)]$(RED) .o files deleted$()$(RESET)"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LINKNAME)
	@make -C ./libft fclean --no-print-directory
	@echo  "$(BLU)[$(NAME)]$(RED) executable file deleted$(RESET)"

re: fclean $(NAME)

.PHONY: all, clean, fclean, re, lib