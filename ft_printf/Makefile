# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 15:56:40 by gmichaud          #+#    #+#              #
#    Updated: 2020/07/10 17:34:14 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

INC_FLAGS = -I./includes

INC_NAME = libft.h

INC_PATH = ./includes

SRC_PATH = src

SRC_NAME = ft_memset.c \
		ft_isdigit.c \
		ft_strchr.c \
		ft_atoi.c \
		ft_putchar.c \
		ft_putstr.c ft_strcat.c  \
		ft_strdel.c ft_strdup.c \
		 ft_strjoin.c ft_strlen.c \
		 ft_strnew.c   \
		ft_nbrlen.c \
		ft_printf/conv1.c \
		ft_printf/conv2.c \
		ft_printf/conv3.c \
		ft_printf/conv4.c \
		ft_printf/conv5.c \
		ft_printf/conv6.c \
		ft_printf/conv7.c \
		ft_printf/double_conv.c \
		ft_printf/fill_tab.c \
		ft_printf/ft_itoa_base.c \
		ft_printf/ft_lltoa.c \
		ft_printf/ft_max.c \
		ft_printf/ft_printf.c \
		ft_printf/long_double_conv.c \
		ft_printf/unsigned_conv.c \
		ft_printf/signed_conv.c \
		ft_printf/print_string.c \
		ft_printf/ft_pow.c \
		ft_printf/ft_abs.c \
		ft_printf/parsing_utils.c \
		ft_printf/ft_endcpy.c


CC = clang

CFLAGS = -Wall -Wextra -Werror

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = obj

OBJ_PATH_PRINTF = ft_printf

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(subst $(SRC_PATH),$(OBJ_PATH),$(OBJ_NAME))

INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

GREEN = \033[32m

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $(OBJ)
	@ranlib $@
	@echo "$(GREEN)[$(NAME)] Compilation success"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)/$(OBJ_PATH_PRINTF) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ -c $<

clean:
	@/bin/rm -f $(OBJ)
	@rmdir $(OBJ_PATH)/$(OBJ_PATH_PRINTF) 2> /dev/null || true
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(GREEN)[$(NAME)] .o files deleted"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)[$(NAME)] executable file deleted"

re: fclean $(NAME)
