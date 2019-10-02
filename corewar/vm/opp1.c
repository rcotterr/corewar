/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 23:08:40 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/25 12:34:09 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	opp_live(t_vm *vm, t_carriage *car, int *args)
{
	int player_number;

	player_number = (-1) * args[0];
	car->live = vm->cycle_number;
	if (player_number > 0 && player_number <= vm->num_of_players
								&& vm->champs[player_number - 1])
	{
		vm->last_champ_alive = vm->champs[player_number - 1];
		if (vm->flags.live)
		{
			ft_putstr("A process shows that player ");
			ft_putnbr(player_number);
			ft_putstr(" (");
			ft_putstr(vm->champs[player_number - 1]->name);
			ft_putendl(") is alive");
		}
	}
	vm->live_since_last_check += 1;
	car->opcode = 0;
	car->position += car->step;
}

void	opp_ld(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int ld_result;

	if (arg_types[0] == T_IND)
		args[0] = get_int_arg(&vm->arena[arena_ind(
				car->position + args[0] % IDX_MOD)], 4);
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

void	opp_st(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int adress;

	if (!check_registr(car, args[0]))
		return ;
	args[0] = get_int_arg(car->regs[args[0] - 1], REG_SIZE);
	if (arg_types[1] == T_IND)
	{
		adress = car->position + args[1] % IDX_MOD;
		if (adress < 0)
			adress += MEM_SIZE;
		int_to_bytes(args[0], vm->arena, adress);
		if (vm->flags.v)
			change_arena_col(vm->vis->arena_colour, adress, car->colour);
	}
	else if (arg_types[1] == T_REG)
	{
		if (!check_registr(car, args[1]))
			return ;
		int_to_bytes(args[0], car->regs[args[1] - 1], 0);
	}
	car->opcode = 0;
	car->position += car->step;
}

void	opp_add(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int		i;
	int		add_result;
	t_vm	*vm_copy;

	vm_copy = vm;
	i = 0;
	while (i < g_op_tab[car->opcode - 1].nb_arg - 1)
	{
		if (arg_types[i] == T_REG)
		{
			if (!check_registr(car, args[i]))
				return ;
			args[i] = get_int_arg(car->regs[args[i] - 1], REG_SIZE);
		}
		i++;
	}
	add_result = args[0] + args[1];
	if (!check_registr(car, args[2]))
		return ;
	int_to_bytes(add_result, car->regs[args[2] - 1], 0);
	change_carry(car, add_result);
	car->opcode = 0;
	car->position += car->step;
}

void	opp_sub(t_vm *vm, t_carriage *car, int *args, t_arg_type *arg_types)
{
	int		i;
	int		sub_result;
	t_vm	*vm_copy;

	vm_copy = vm;
	i = 0;
	while (i < g_op_tab[car->opcode - 1].nb_arg - 1)
	{
		if (arg_types[i] == T_REG)
		{
			if (!check_registr(car, args[i]))
				return ;
			args[i] = get_int_arg(car->regs[args[i] - 1], REG_SIZE);
		}
		i++;
	}
	sub_result = args[0] - args[1];
	if (!check_registr(car, args[2]))
		return ;
	int_to_bytes(sub_result, car->regs[args[2] - 1], 0);
	change_carry(car, sub_result);
	car->opcode = 0;
	car->position += car->step;
}
