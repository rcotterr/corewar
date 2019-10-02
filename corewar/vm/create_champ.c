/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_champ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 06:33:30 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/14 13:46:36 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ			*new_champ(void)
{
	t_champ	*champ;

	champ = ft_memalloc(sizeof(t_champ));
	champ->exec_code = NULL;
	champ->size = 0;
	champ->name = NULL;
	champ->player_number = 0;
	champ->comment = NULL;
	return (champ);
}

int				crash(char *s)
{
	ft_putendl(s);
	exit(-1);
}

t_champ			*create_champ(t_champ_info champ_info, char *arg)
{
	t_champ		*champ;
	int			skip;

	champ = new_champ();
	if (!(check_header(champ_info.info)))
	{
		ft_putstr(arg);
		crash(" has an invalid header!");
	}
	skip = COREWAR_MAGIC_LENGTH;
	champ->name = get_champ_name(champ_info.info + skip);
	skip += PROG_NAME_LENGTH;
	if (!(check_null(champ_info.info + skip)))
		return (NULL);
	skip += NULL_LENGTH;
	champ->size = get_champ_size(champ_info.info + skip);
	skip += COREWAR_SIZE_LENGTH;
	champ->comment = get_champ_comment(champ_info.info + skip);
	skip += COMMENT_LENGTH;
	if (!(check_null(champ_info.info + skip)))
		return (NULL);
	skip += NULL_LENGTH;
	champ->exec_code = get_champ_exec_code(champ_info);
	return (champ);
}

void			print_champ(t_champ *champ)
{
	int i;

	i = 0;
	if (!champ)
	{
		ft_putendl("empty_champ!");
		return ;
	}
	ft_putstr("Player number ");
	ft_putnbr(champ->player_number);
	ft_putchar('\n');
	ft_putnbr(champ->size);
	ft_putchar('\n');
	ft_putendl(champ->name);
	ft_putendl(champ->comment);
	ft_putstr("champ_exec_code is: ");
	while (i < champ->size)
	{
		ft_putnbr((champ->exec_code)[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}
