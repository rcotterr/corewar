/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 12:29:52 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/14 14:10:24 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			write_colour(t_byte *ar_col, t_byte to_write, int pos, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		ar_col[pos + i % MEM_SIZE] = to_write;
		i++;
	}
}

unsigned char	*fill_arena_colour(t_vm vm, unsigned char *arena_col)
{
	int i;
	int	mem_part_size;

	mem_part_size = MEM_SIZE / vm.num_of_players;
	i = 0;
	while (i < vm.num_of_players)
	{
		write_colour(arena_col, i + 1, mem_part_size * i, vm.champs[i]->size);
		i++;
	}
	return (arena_col);
}

int				*make_colour(void)
{
	int	*colour;

	colour = ft_memalloc(sizeof(int) * (MAX_PLAYERS + 1));
	colour[0] = GREY;
	colour[1] = PINK;
	colour[2] = YELLOW;
	colour[3] = GREEN;
	colour[4] = BLUE;
	return (colour);
}

void			col_carrigies(t_vm *vm)
{
	t_car_list	*car;
	int			i;

	car = vm->car_list;
	i = vm->num_of_players - 1;
	while (car)
	{
		car->car->colour = -1 * get_int_arg((car->car->regs)[0], REG_SIZE);
		car = car->next;
		i--;
	}
}
