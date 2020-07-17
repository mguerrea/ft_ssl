# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/10 12:59:25 by mguerrea          #+#    #+#              #
#    Updated: 2020/07/17 18:01:23 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES =

C_FILES_md5 = md5.c transform.c update.c utils.c bit_functions.c

C_FILES_ssl = main.c bit_functions.c print.c

C_FILES_sha = sha256.c update.c transform.c bit_functions.c init.c sha224.c

C_FILES_base64 = base64.c encode.c decode.c

C_FILES_des = des.c tables.c

C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))