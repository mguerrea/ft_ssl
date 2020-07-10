# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    includes.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/10 13:14:34 by mguerrea          #+#    #+#              #
#    Updated: 2020/07/10 13:15:36 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

H_FILES =

H_FILES_md5 = md5.h

H_FILES_ssl =

H_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(H_FILES_$(SUB_DIR))))
