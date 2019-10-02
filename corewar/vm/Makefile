# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 16:03:39 by rcotter-          #+#    #+#              #
#    Updated: 2019/09/25 13:00:16 by rcotter-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../corewar
MINILIB = minilibx_macos/libmlx.a
SOURCES = create_champ.c get_info.c check.c vm.c carriage.c visual.c colour.c draw1.c draw2.c ft_hex.c run_game.c op.c do_opp.c fun.c opp1.c opp2.c opp3.c opp4.c flag.c print.c make_num_players.c process_arg.c arena.c check_in_cycle.c
HEADERS = carriage.h op.h opp1.h opp2.h opp3.h opp4.h vm.h fun_tub.h
all: $(NAME)

$(NAME): $(SOURCES) main.c $(HEADERS)
	make -C ../libft/
	gcc $(SOURCES) main.c -Wall -Wextra -Werror -I. ../libft/libft.a -lmlx -framework OpenGL -framework AppKit -o $(NAME)
clean:
	make -C ../libft/ clean
fclean: clean
	rm -f $(NAME)
	make -C ../libft/ fclean
re: fclean all/
norm:
	norminette main.c $(SOURCES) $(HEADERS)
