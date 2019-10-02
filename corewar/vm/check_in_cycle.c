/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:28:27 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/25 12:32:55 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	manage_dying(t_vm *vm)
{
	t_car_list	*car;
	t_car_list	*prev;
	t_car_list	*tmp;

	prev = NULL;
	car = vm->car_list;
	while (car)
	{
		if (vm->cycle_number - car->car->live >= vm->cycles_to_die)
		{
			tmp = car;
			if (!prev)
				vm->car_list = car->next;
			else
				prev->next = car->next;
			car = car->next;
			free(tmp->car);
			tmp->car = NULL;
			free(tmp);
			tmp = NULL;
			continue ;
		}
		prev = car;
		car = car->next;
	}
}

void	handle_waiting(t_vm *vm, t_car_list *car)
{
	int			opp_code;

	if (car->car->waiting == 0)
	{
		opp_code = vm->arena[car->car->position % MEM_SIZE];
		if (opp_code >= 1 && opp_code <= 16)
		{
			car->car->opcode = opp_code;
			car->car->waiting = (g_op_tab[opp_code - 1]).cycle;
		}
	}
	if (car->car->waiting > 0)
		car->car->waiting -= 1;
	car = car->next;
}

int		need_check(t_vm *vm)
{
	if (vm->cycles_to_die <= 0)
		return (1);
	else if (vm->turns_since_last_check >= vm->cycles_to_die)
		return (1);
	return (0);
}

void	modify_cycles_to_die(t_vm *vm)
{
	if (vm->live_since_last_check >= NBR_LIVE ||
	vm->checks_since_last_change == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks_since_last_change = 0;
	}
	vm->checks_since_last_change += 1;
}
