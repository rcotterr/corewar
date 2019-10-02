# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/03 15:22:31 by tdontos-          #+#    #+#              #
#    Updated: 2019/09/15 19:44:13 by kmurch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM	= ../asm
NAME_DIS	= ../disasm

SRCDIR	= ./src
OBJDIR	= ./obj

ASM		= /asm/
DIS		= /disasm/

SRC_ASM		=	asm.c print.c pars.c op.c operation.c read_arg.c opers_list.c valid.c \
			opers_type.c opers_error1.c cmd.c opers_error2.c opers_error.c \
			opers_check_dir_reg.c opers_check_ins_sep.c opers_check_all.c \
			opers_is_type.c opers_is_type2.c valid2.c opers_val_label.c
SRC_DIS		=	disasm.c utility.c output.c op.c
	
OBJ_ASM		= $(addprefix $(OBJDIR)/,$(SRC_ASM:.c=.o))
OBJ_DIS		= $(addprefix $(OBJDIR)/,$(SRC_DIS:.c=.o)) $(addprefix $(OBJDIR)/,$(op.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
FTDIR	= ../libft
FT_LIB	= $(addprefix $(FTDIR)/,libft.a)
FT_INC	= -I $(FTDIR)
FT_LNK	= -L $(FTDIR) -l ft

all: obj $(FT_LIB) $(NAME_DIS) $(NAME_ASM)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)$(ASM)%.c inc/asm.h inc/op.h
	$(CC) $(CFLAGS) $(FT_INC) -o $@ -c $<

$(OBJDIR)/%.o:$(SRCDIR)$(DIS)%.c inc/disasm.h inc/op.h
	$(CC) $(CFLAGS) $(FT_INC) -o $@ -c $<

$(FT_LIB):
	make -C $(FTDIR)

$(NAME_ASM): $(OBJ_ASM)
	$(CC) $(OBJ_ASM) $(FT_LNK) -o $(NAME_ASM)

$(NAME_DIS): $(OBJ_DIS)
	$(CC) $(OBJ_DIS) $(FT_LNK) -o $(NAME_DIS)

clean:
	rm -rf $(OBJDIR)
	make -C $(FTDIR) clean	

fclean: clean
	rm -f $(NAME_ASM)
	rm -f $(NAME_DIS)
	make -C $(FTDIR) fclean	

re: fclean all

norm:
	norminette $(addprefix src/asm/, $(SRC_ASM)) $(addprefix src/disasm/, $(SRC_DIS)) inc/asm.h inc/disasm.h inc/op.h
