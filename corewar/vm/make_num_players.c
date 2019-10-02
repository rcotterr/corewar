/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_num_players.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:02:26 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/14 14:31:17 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		repeat_num(t_vm *vm, int num)
{
	int i;

	i = 0;
	while (vm->champs[i])
	{
		if ((vm->champs[i])->player_number == num)
			return (1);
		i++;
	}
	return (0);
}

void	swap(t_champ **champ1, t_champ **champ2)
{
	t_champ *tmp;

	tmp = *champ1;
	*champ1 = *champ2;
	*champ2 = tmp;
}

int		order_num_players(t_champ **champs, int num_of_all)
{
	int i;

	i = 0;
	while (champs[i])
	{
		if ((champs[i])->player_number > num_of_all)
			crash("Number of player is bigger than common quantity of players");
		if ((champs[i])->player_number != i + 1)
		{
			swap(&champs[i], &champs[(champs[i])->player_number - 1]);
			continue ;
		}
		i++;
	}
	return (0);
}

void	make_num_players(t_vm *vm)
{
	int i;
	int num;

	i = 0;
	num = 1;
	while (vm->champs[i])
	{
		if (!((vm->champs[i])->player_number))
		{
			if (!(repeat_num(vm, num)))
			{
				(vm->champs[i])->player_number = num;
				num++;
				i++;
			}
			else
				num++;
		}
		else
			i++;
	}
	vm->num_of_players = i;
	order_num_players(vm->champs, vm->num_of_players);
}
