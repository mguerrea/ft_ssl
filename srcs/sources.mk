# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/10 12:59:25 by mguerrea          #+#    #+#              #
#    Updated: 2020/07/11 17:53:07 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES =

C_FILES_md5 = md5.c transform.c update.c utils.c bit_functions.c

C_FILES_ssl = main.c bit_functions.c

C_FILES_sha = sha256.c update.c transform.c bit_functions.c

C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))