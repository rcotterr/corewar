/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 23:12:50 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/25 12:33:48 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	opp_and(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int	and_result;
	int	i;

	i = 0;
	while (i < g_op_tab[car->opcode - 1].nb_arg - 1)
	{
		if (arg_types[i] == T_REG)
		{
			if (!check_registr(car, args[i]))
				return ;
			args[i] = get_int_arg(car->regs[args[i] - 1], REG_SIZE);
		}
		if (arg_types[i] == T_IND)
			args[i] = get_int_arg(&vm->arena[arena_ind(car->position + args[i]
									% IDX_MOD)], 4);
		i++;
	}
	and_result = args[0] & args[1];
	if (!check_registr(car, args[2]))
		return ;
	int_to_bytes(and_result, car->regs[args[2] - 1], 0);
	change_carry(car, and_result);
	car->opcode = 0;
	car->position += car->step;
}

void	opp_or(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int	or_result;
	int	i;

	i = 0;
	while (i < g_op_tab[car->opcode - 1].nb_arg - 1)
	{
		if (arg_types[i] == T_REG)
		{
			if (!check_registr(car, args[i]))
				return ;
			args[i] = get_int_arg(car->regs[args[i] - 1], REG_SIZE);
		}
		if (arg_types[i] == T_IND)
			args[i] = get_int_arg(&vm->arena[arena_ind(car->position + args[i]
									% IDX_MOD)], 4);
		i++;
	}
	or_result = args[0] | args[1];
	if (!check_registr(car, args[2]))
		return ;
	int_to_bytes(or_result, car->regs[args[2] - 1], 0);
	change_carry(car, or_result);
	car->opcode = 0;
	car->position += car->step;
}

void	opp_xor(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int	xor_result;
	int	i;

	i = 0;
	while (i < g_op_tab[car->opcode - 1].nb_arg - 1)
	{
		if (arg_types[i] == T_REG)
		{
			if (!check_registr(car, args[i]))
				return ;
			args[i] = get_int_arg(car->regs[args[i] - 1], REG_SIZE);
		}
		if (arg_types[i] == T_IND)
			args[i] = get_int_arg(&vm->arena[arena_ind(car->position + args[i]
									% IDX_MOD)], 4);
		i++;
	}
	xor_result = args[0] ^ args[1];
	if (!check_registr(car, args[2]))
		return ;
	int_to_bytes(xor_result, car->regs[args[2] - 1], 0);
	change_carry(car, xor_result);
	car->opcode = 0;
	car->position += car->step;
}

void	opp_zjmp(t_vm *vm, t_carriage *car, int *args)
{
	t_vm	*vm_copy;

	vm_copy = vm;
	if (car->carry == 1)
	{
		car->position = car->position + args[0] % IDX_MOD;
		if (car->position < 0)
			car->position += MEM_SIZE;
	}
	else
		car->position += car->step;
	car->opcode = 0;
}

void	opp_ldi(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int i;
	int adress;

	i = 0;
	while (i < g_op_tab[car->opcode - 1].nb_arg - 1)
	{
		if (arg_types[i] == T_REG)
		{
			if (!check_registr(car, args[i]))
				return ;
			args[i] = get_int_arg(car->regs[args[i] - 1], REG_SIZE);
		}
		if (arg_types[i] == T_IND)
			args[i] = get_int_arg(&vm->arena[arena_ind(car->position + args[i]
									% IDX_MOD)], 4);
		i++;
	}
	adress = car->position + (args[0] + args[1]) % IDX_MOD;
	if (!check_registr(car, args[2]))
		return ;
	write_to_reg(vm, car, args, adress);
	car->opcode = 0;
	car->position += car->step;
}
