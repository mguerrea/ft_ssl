# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/10 12:59:25 by mguerrea          #+#    #+#              #
#    Updated: 2020/09/08 12:54:39 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES =

C_FILES_md5 = md5.c transform.c update.c utils.c bit_functions.c

C_FILES_ssl = main.c bit_functions.c print.c pbkdf.c utils.c

C_FILES_sha = sha256.c update.c transform.c bit_functions.c init.c sha224.c \
	hmac.c

C_FILES_base64 = base64.c encode.c decode.c decode_buff.c

C_FILES_des = des.c tables.c encrypt.c key_schedule.c permutations.c \
	parsing.c des64.c pass.c error.c

C_FILES_des += des_ecb.c des_cbc.c des_cfb.c des_ofb.c \
	des_ede_ecb.c des_ede_cbc.c des_ede_cfb.c des_ede_ofb.c \
	des_ede3_ecb.c des_ede3_cbc.c des_ede3_cfb.c des_ede3_ofb.c

C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))