/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:52:43 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/14 14:24:04 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		is_flag(char *arg)
{
	int i;
	int ret;

	i = 1;
	ret = 0;
	if (ft_strcmp(&arg[i], FLAG_DUMP))
		ret = 1;
	else if (ft_strcmp(&arg[i], FLAG_DUMP))
		ret = 1;
	else if (ft_strcmp(&arg[i], FLAG_VIS))
		ret = 1;
	else if (ft_strcmp(&arg[i], FLAG_LIVE))
		ret = 1;
	else if (ft_strcmp(&arg[i], FLAG_DEBUG))
		ret = 1;
	return (ret);
}

int		take_next_arg_num(char *arg)
{
	int num;

	num = 0;
	if (arg && is_number(arg))
		num = ft_atoi(arg);
	else
		crash("Wrong use of flugs");
	return (num);
}

void	process_flags(t_vm *vm, char **argv)
{
	int		i;
	char	*arg;

	i = 1;
	arg = argv[0];
	if (!(ft_strcmp(&arg[i], FLAG_DUMP)))
	{
		(vm->flags).dump = 1;
		(vm->flags).dump_num = take_next_arg_num(argv[i]);
	}
	else if (!(ft_strcmp(&arg[i], FLAG_NUM)))
		(vm->flags).n = take_next_arg_num(argv[i]);
	else if (!(ft_strcmp(&arg[i], FLAG_VIS)))
		(vm->flags).v = 1;
	else if (!(ft_strcmp(&arg[i], FLAG_DEBUG)))
	{
		(vm->flags).v = 1;
		(vm->flags).v_debug = 1;
	}
	else if (!(ft_strcmp(&arg[i], FLAG_LIVE)))
		(vm->flags).live = 1;
}

void	process_flag_n(t_vm *vm, t_champ *champ)
{
	if (vm->flags.n < 1 || vm->flags.n > 4)
		crash("Wrong number of a player in flag '-n'");
	champ->player_number = vm->flags.n;
	vm->flags.n = 0;
}

void	process_flag_dump(t_vm *vm)
{
	if (vm->cycle_number == vm->flags.dump_num)
	{
		print_arena_32(vm->arena);
		exit(0);
	}
}
