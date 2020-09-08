# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/30 16:49:08 by mguerrea          #+#    #+#              #
#    Updated: 2018/11/18 12:21:25 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_NAME = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_isblank.c \
		ft_isspace.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putchar_color.c \
		ft_putstr_color.c \
		ft_itoa.c \
		ft_sanitol.c \
		ft_max.c \
		ft_min.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_list_to_str.c \
		ft_lstaddback.c \
		ft_elemdel.c \
		ft_count_elem.c \
		ft_putstr_free.c \
		ft_putendl_free.c \
		ft_nbrlen.c \
		ft_lstlast.c \
		ft_realloc.c \
		get_next_line.c \
		free_tab.c \
		ft_strndup.c \
		split_quotes.c \
		tablen.c

SRC_PRINTF = ft_printf/conv1.c \
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

SRC_NAME += $(SRC_PRINTF)

INC_NAME = libft.h

INC_PATH = ./includes

INC_FLAGS = -I./includes

LIB_FLAGS =

LIBS =

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRC_PATH = src

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = obj

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(subst $(SRC_PATH),$(OBJ_PATH),$(OBJ_NAME))

INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

RED = \x1B[31m
GRN = \x1B[32m
YEL = \x1B[33m
BLU = \x1B[34m
MAG = \x1B[35m
CYN = \x1B[36m
WHT = \x1B[37m
RESET = \x1B[0m
ERASE = \033[2K

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $(OBJ)
	@ranlib $@
	@echo "\n$(BLU)[$(NAME)]$(GRN) Compilation success$(RESET)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/ft_printf
	@$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ -c $<
	@echo "\r$(ERASE)$(BLU)[$(NAME)]$(RESET) $@ created\c"

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(OBJ_PATH)
	@echo "$(BLU)[$(NAME)]$(RED) .o files deleted$()$(RESET)"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LINKNAME)
	@echo  "$(BLU)[$(NAME)]$(RED) executable file deleted$(RESET)"

re: fclean $(NAME)

.PHONY: all, clean, fclean, re
