/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 00:14:46 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/25 11:40:52 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "carriage.h"

t_byte		*int_to_bytes(int ints, t_byte *where, int ind)
{
	union u_byte	byte;
	int				i;
	int				j;

	i = 0;
	j = ind;
	byte.ints = ints;
	byte.ints = reverse(byte.ints, 4);
	while (i < 4)
	{
		where[arena_ind(j)] = byte.chars[i];
		i++;
		j++;
	}
	return (where);
}

t_carriage	*create_carriage(int player_num)
{
	t_carriage	*new_carriage;

	new_carriage = ft_memalloc(sizeof(t_carriage));
	int_to_bytes(-1 * player_num, (new_carriage->regs)[0], 0);
	new_carriage->carry = 0;
	new_carriage->live = 0;
	new_carriage->step = 0;
	new_carriage->waiting = 0;
	new_carriage->opcode = 0;
	new_carriage->colour = 0;
	new_carriage->id = 0;
	return (new_carriage);
}

t_carriage	*fork_carriage(t_carriage *car, int position)
{
	t_carriage	*copy;
	int			i;
	int			j;

	copy = ft_memalloc(sizeof(t_carriage));
	i = 0;
	j = 0;
	while (i < REG_NUMBER)
	{
		while (j < REG_SIZE)
		{
			copy->regs[i][j] = car->regs[i][j];
			j++;
		}
		i++;
		j = 0;
	}
	copy->carry = car->carry;
	copy->position = car->position + position % IDX_MOD;
	copy->step = 0;
	copy->live = car->live;
	copy->opcode = 0;
	copy->waiting = 0;
	copy->colour = car->colour;
	return (copy);
}
