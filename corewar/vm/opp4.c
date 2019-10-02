/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 23:18:25 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/25 12:34:39 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	opp_aff(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	char		aff_result;
	t_vm		*vm_copy;
	t_arg_type	*arg_types_copy;

	vm_copy = vm;
	arg_types_copy = arg_types;
	if (!check_registr(car, args[0]))
		return ;
	args[0] = get_int_arg(car->regs[args[0] - 1], REG_SIZE);
	aff_result = (char)args[0];
	ft_putchar_fd(aff_result, 2);
	car->opcode = 0;
	car->position += car->step;
}

void	change_carry(t_carriage *car, int result)
{
	if (result)
		car->carry = 0;
	else
		car->carry = 1;
}

void	write_to_reg(t_vm *vm, t_carriage *car, int *args, int adress)
{
	int i;

	i = 0;
	while (i < REG_SIZE)
	{
		car->regs[args[2] - 1][i] = vm->arena[arena_ind(adress + i)];
		i++;
	}
}
