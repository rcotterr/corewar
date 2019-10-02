/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 06:33:50 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/25 13:00:30 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_usage(void)
{
	ft_putstr("Usage: ./corewar ");
	ft_putendl("[-dump N | -v | -debug | -n N] <champion1.cor> <...>");
	ft_putendl("-dump N	: Dumps memory after N cycles then exits");
	ft_putendl("-n N	: sets the N number of the next player");
	ft_putendl("-v      : visualisation");
	ft_putendl("-debug  : step by step visualisation");
	exit(0);
}

int		main(int argc, char **argv)
{
	int			i;
	t_vm		vm;
	t_visual	vis;

	if (argc == 1)
		print_usage();
	i = 1;
	vm = create_vm();
	while (i < argc)
	{
		process_arg(&vm, &argv[i]);
		i++;
	}
	make_num_players(&vm);
	init_arena(&vm);
	if (!(vm.flags.v))
	{
		print_players(vm);
		game_cycle(&vm);
		print_winner(vm);
	}
	else
		vis = visual(vm);
	exit(0);
}
