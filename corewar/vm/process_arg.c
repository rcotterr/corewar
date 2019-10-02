/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:08:43 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/14 14:01:18 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ	*process_champ(t_vm *vm, char *arg)
{
	int				fd;
	t_champ_info	champ_info;
	t_champ			*champ;

	fd = open(arg, O_RDONLY);
	champ_info = get_champ_info(fd);
	if (!champ_info.info)
		return (NULL);
	champ = create_champ(champ_info, arg);
	if (!champ)
	{
		ft_putstr(arg);
		crash(" is invalid!");
	}
	validate_champ(champ, champ_info);
	free(champ_info.info);
	champ_info.info = NULL;
	if (!(vm->flags.n))
		champ->player_number = 0;
	else
		process_flag_n(vm, champ);
	close(fd);
	return (champ);
}

int		is_number(char *arg)
{
	int i;

	i = 0;
	while (ft_isdigit(arg[i]))
		i++;
	if (!(arg[i]))
		return (1);
	else
		return (0);
}

void	process_arg(t_vm *vm, char **argv)
{
	int			i;
	char		*arg;
	static int	champ_ind;

	i = 0;
	arg = argv[i];
	if (arg[i] == '-' && is_flag(arg))
		process_flags(vm, argv);
	else if ((vm->flags.n || vm->flags.dump) && is_number(arg))
		return ;
	else
	{
		if (champ_ind < MAX_PLAYERS)
		{
			(vm->champs)[champ_ind] = process_champ(vm, arg);
			champ_ind++;
		}
		else
			crash("TOO MANY PLAYERS");
	}
}
