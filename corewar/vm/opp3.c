/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 23:16:25 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/25 12:33:28 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	opp_sti(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int adress;
	int i;

	i = 0;
	while (i < g_op_tab[car->opcode - 1].nb_arg)
	{
		if (arg_types[i] == T_REG)
		{
			if (!check_registr(car, args[i]))
				return ;
			args[i] = get_int_arg(car->regs[args[i] - 1], REG_SIZE);
		}
		i++;
	}
	if (arg_types[1] == T_IND)
		args[1] = get_int_arg(&vm->arena[car->position + args[1] % IDX_MOD], 4);
	adress = car->position + (args[1] + args[2]) % IDX_MOD;
	if (adress < 0)
		adress += MEM_SIZE;
	int_to_bytes(args[0], vm->arena, adress);
	if (vm->flags.v)
		change_arena_col(vm->vis->arena_colour, adress, car->colour);
	car->opcode = 0;
	car->position += car->step;
}

void	opp_fork(t_vm *vm, t_carriage *car, int *args)
{
	t_car_list *copy;
	t_car_list *tmp;

	copy = ft_memalloc(sizeof(t_car_list));
	copy->car = fork_carriage(car, args[0] % IDX_MOD);
	copy->car->id = vm->car_list->car->id + 1;
	tmp = vm->car_list;
	copy->next = tmp;
	vm->car_list = copy;
	car->opcode = 0;
	car->position += car->step;
}

void	opp_lld(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int ld_result;

	if (arg_types[0] == T_IND)
		args[0] = get_int_arg(&vm->arena[
				arena_ind(car->position + args[0])], 4);
	ld_result = args[0];
	if (!check_registr(car, args[1]))
		return ;
	int_to_bytes(ld_result, car->regs[args[1] - 1], 0);
	if (ld_result)
		car->carry = 0;
	else
		car->carry = 1;
	car->opcode = 0;
	car->position += car->step;
}

void	opp_lldi(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
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
			args[i] = get_int_arg(&vm->arena[arena_ind(car->position
									+ args[i] % IDX_MOD)], 4);
		i++;
	}
	adress = car->position + (args[0] + args[1]);
	if (!check_registr(car, args[2]))
		return ;
	write_to_reg(vm, car, args, adress);
	car->opcode = 0;
	car->position += car->step;
}

void	opp_lfork(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	t_car_list	*copy;
	t_car_list	*tmp;
	t_arg_type	*arg_types_copy;

	arg_types_copy = arg_types;
	copy = ft_memalloc(sizeof(t_car_list));
	while (args[0] < 0)
		args[0] += MEM_SIZE;
	copy->car = fork_carriage(car, args[0]);
	copy->car->id = vm->car_list->car->id + 1;
	copy->car->position = car->position + args[0];
	tmp = vm->car_list;
	copy->next = tmp;
	vm->car_list = copy;
	car->opcode = 0;
	car->position += car->step;
}
