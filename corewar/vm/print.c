/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:58:56 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/25 12:59:21 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_vm_champs(t_vm vm)
{
	int	i;

	i = 0;
	while (vm.champs[i])
	{
		print_champ(vm.champs[i]);
		i++;
	}
}

void	print_arena_32(unsigned char *arena)
{
	int		i;
	char	*s;
	char	*tmp;

	i = 0;
	while (i < MEM_SIZE)
	{
		s = ft_hex(arena[i], 1);
		if (ft_strlen(s) == 1)
		{
			tmp = s;
			s = ft_strjoin("0", s);
			free(tmp);
		}
		ft_putstr(s);
		free(s);
		i++;
		if (!(i % 32))
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

void	print_cars(t_car_list *car)
{
	t_car_list *tmp;

	tmp = car;
	while (tmp)
	{
		ft_putnbr(get_int_arg((tmp->car->regs)[0], 4));
		tmp = tmp->next;
		ft_putchar('\n');
	}
}

void	print_players(t_vm vm)
{
	int		i;
	t_champ	*champ;

	i = 0;
	ft_putendl("Introducing players...");
	while (i < vm.num_of_players)
	{
		champ = vm.champs[i];
		ft_putstr("* Player ");
		ft_putnbr(champ->player_number);
		ft_putstr(", weighing ");
		ft_putnbr(champ->size);
		ft_putstr(" bytes, ");
		ft_putchar('"');
		ft_putstr(champ->name);
		ft_putchar('"');
		ft_putstr(" (");
		ft_putchar('"');
		ft_putstr(champ->comment);
		ft_putchar('"');
		ft_putendl(") !");
		i++;
	}
}

void	print_winner(t_vm vm)
{
	if (!(vm.last_champ_alive))
		crash("There is no winner");
	ft_putstr("Player ");
	ft_putnbr((vm.last_champ_alive)->player_number);
	ft_putstr(" (");
	ft_putstr((vm.last_champ_alive)->name);
	ft_putendl(") won!");
}
