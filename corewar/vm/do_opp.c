/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_opp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 05:23:57 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/24 15:36:53 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "carriage.h"
#include "vm.h"
#include "fun_tub.h"

void	to_arg_type(char coddage, t_arg_type *arg_types)
{
	int i;

	arg_types[0] = (coddage & 0xC0) >> 6;
	arg_types[1] = (coddage & 0x30) >> 4;
	arg_types[2] = (coddage & 0xC) >> 2;
	i = 0;
	while (i < 3)
	{
		if (arg_types[i] == 3)
			arg_types[i] = 4;
		i++;
	}
}

int		arg_type_size(t_arg_type argt)
{
	if (argt == T_REG)
		return (1);
	if (argt == T_DIR)
		return (DIR_SIZE);
	if (argt == T_IND)
		return (IND_SIZE);
	return (0);
}

int		read_arg_types(t_vm *vm, t_carriage *car, t_arg_type *arg_types)
{
	int		i;
	char	coddage;

	i = 0;
	if (g_op_tab[car->opcode - 1].octal)
	{
		coddage = vm->arena[arena_ind(car->position + car->step)];
		to_arg_type(coddage, arg_types);
		car->step += 1;
	}
	else
	{
		while (i < g_op_tab[car->opcode - 1].nb_arg)
		{
			arg_types[i] = g_op_tab[car->opcode - 1].args[i];
			i++;
		}
	}
	return (1);
}

int		read_opp_args(t_vm *vm, t_carriage *car, int *args,
						t_arg_type *arg_types)
{
	int			i;
	int			size;

	if (!read_arg_types(vm, car, arg_types))
		return (0);
	i = 0;
	while (i < g_op_tab[car->opcode - 1].nb_arg)
	{
		if (arg_types[i] == T_DIR && g_op_tab[car->opcode - 1].label)
			size = 2;
		else
			size = arg_type_size(arg_types[i]);
		args[i] = get_int_arg(&vm->arena[arena_ind(car->position +
								car->step)], size);
		car->step += size;
		i++;
	}
	i = 0;
	while (i < g_op_tab[car->opcode - 1].nb_arg)
	{
		if (!(g_op_tab[car->opcode - 1].args[i] & arg_types[i]))
			return (0);
		i++;
	}
	return (1);
}

void	do_opp(t_vm *vm, t_carriage *car)
{
	int			args[3];
	char		opcode;
	t_arg_type	arg_types[3];

	opcode = car->opcode;
	if (opcode >= 1 && opcode <= 16)
	{
		car->step += 1;
		if (read_opp_args(vm, car, args, arg_types))
		{
			(g_fun_tab[opcode - 1]).fun(vm, car, args, arg_types);
			car->step = 0;
		}
		else
		{
			car->position += car->step;
			car->step = 0;
			car->opcode = 0;
		}
	}
	else
		car->position += 1;
	car->position = car->position % MEM_SIZE;
}
