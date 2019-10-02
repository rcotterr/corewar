/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 21:18:35 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/25 13:00:39 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	carriages_do_their_things(t_vm *vm)
{
	t_car_list	*car;

	car = vm->car_list;
	while (car)
	{
		handle_waiting(vm, car);
		if (car->car->waiting == 0)
			do_opp(vm, car->car);
		car = car->next;
	}
}

int		step(t_vm *vm)
{
	if (vm->car_list)
	{
		carriages_do_their_things(vm);
		vm->turns_since_last_check += 1;
		if (need_check(vm))
		{
			manage_dying(vm);
			modify_cycles_to_die(vm);
			vm->turns_since_last_check = 0;
			vm->live_since_last_check = 0;
		}
		if (vm->flags.dump)
			process_flag_dump(vm);
		if (vm->car_list)
			vm->cycle_number += 1;
		if (vm->flags.v)
			change_window(vm);
	}
	else
	{
		if (vm->flags.v)
			vis_winner(vm);
	}
	return (0);
}

void	game_cycle(t_vm *vm)
{
	while (vm->car_list)
	{
		step(vm);
	}
}
