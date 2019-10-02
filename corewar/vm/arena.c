/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdesmond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 03:25:34 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/12 03:25:37 by jdesmond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		arena_ind(int i)
{
	int	ind;

	if (i < 0)
		ind = (i % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
	else
		ind = i % MEM_SIZE;
	return (ind);
}

void	write_to_arena(t_vm *vm, t_byte *to_write, int position, int length)
{
	int i;

	i = 0;
	while (i < length)
	{
		vm->arena[arena_ind((position + i))] = to_write[i];
		i++;
	}
}

void	change_arena_col(unsigned char *arena_col, int adress, int col)
{
	int i;

	i = 0;
	while (i < 4)
	{
		arena_col[arena_ind(adress + i)] = col;
		i++;
	}
}
