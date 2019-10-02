/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 21:09:49 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/24 15:38:44 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_arena(t_vm *vm)
{
	int			i;
	int			mem_part_size;
	t_car_list	*car;

	mem_part_size = MEM_SIZE / vm->num_of_players;
	i = -1;
	while (++i < vm->num_of_players)
	{
		write_to_arena(vm, vm->champs[i]->exec_code,
				mem_part_size * i, vm->champs[i]->size);
		car = ft_memalloc(sizeof(t_car_list));
		car->car = create_carriage(vm->champs[i]->player_number);
		car->car->position = i * mem_part_size;
		if (vm->car_list)
		{
			car->next = vm->car_list;
			car->car->id = vm->car_list->car->id + 1;
		}
		else
		{
			car->next = NULL;
			car->car->id = 1;
		}
		vm->car_list = car;
	}
}

t_flag	init_flag(void)
{
	t_flag flag;

	flag.dump = 0;
	flag.n = 0;
	flag.v = 0;
	flag.live = 0;
	flag.v_debug = 0;
	return (flag);
}

t_champ	**init_champs(void)
{
	int		i;
	t_champ	**champs;

	i = 0;
	champs = ft_memalloc(sizeof(t_champ) * MAX_PLAYERS + 1);
	while (i < MAX_PLAYERS + 1)
	{
		champs[i] = NULL;
		i++;
	}
	return (champs);
}

t_vm	create_vm(void)
{
	t_vm	vm;

	vm.arena = ft_memalloc(sizeof(t_byte) * MEM_SIZE);
	vm.car_list = NULL;
	vm.champs = ft_memalloc(sizeof(t_champ) * MAX_PLAYERS + 1);
	vm.flags = init_flag();
	vm.cycle_number = 1;
	vm.num_of_players = 0;
	vm.cycles_to_die = CYCLE_TO_DIE;
	vm.checks_since_last_change = 0;
	vm.turns_since_last_check = 0;
	vm.live_since_last_check = 0;
	vm.vis = NULL;
	return (vm);
}
