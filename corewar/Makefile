# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/15 16:44:20 by rcotter-          #+#    #+#              #
#    Updated: 2019/09/15 19:43:47 by kmurch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C asmb/
	make -C vm/
clean:
	make clean -C vm/
	make clean -C asmb/
fclean: clean
	make -C vm/ fclean
	make -C asmb/ fclean
re: fclean all/
norm:
	make -C vm/ norm
	make -C asmb/ norm
