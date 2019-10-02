/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:55:18 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/14 15:51:28 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			validate_champ(t_champ *champ, t_champ_info champ_info)
{
	int real_size;

	real_size = champ_info.len - (COREWAR_MAGIC_LENGTH + PROG_NAME_LENGTH
		+ NULL_LENGTH + COREWAR_SIZE_LENGTH + COMMENT_LENGTH + NULL_LENGTH);
	if (!champ)
		crash("The champion is invalid");
	if (!(champ->size) || champ->size > CHAMP_MAX_SIZE)
		crash("Size of exec code is invalid!");
	if (champ->size != real_size)
		crash("Real size is different!");
	if (!(champ->name) || !(champ->name[0]))
		crash("There is no name!");
	if (!(champ->comment) || !(champ->comment[0]))
		crash("There is no comment!");
	if (ft_strlen(champ->name) > PROG_NAME_LENGTH)
		crash("Too long name!");
}

unsigned int	reverse(unsigned int x, int size)
{
	x = (x & 0x00FF00FF) << 8 | (x & 0xFF00FF00) >> 8;
	if (size == 4)
		x = (x & 0x0000FFFF) << 16 | (x & 0xFFFF0000) >> 16;
	return (x);
}

int				check_header(char *champ_info)
{
	int				i;
	int				ret;
	int				magic_h;
	union u_byte	byte;

	i = 0;
	byte.ints = 0;
	while (i < COREWAR_MAGIC_LENGTH)
	{
		byte.chars[i] = champ_info[i];
		i++;
	}
	magic_h = reverse(byte.ints, COREWAR_MAGIC_LENGTH);
	if (magic_h == COREWAR_EXEC_MAGIC)
		ret = 1;
	else
		ret = 0;
	return (ret);
}

int				check_null(char *champ_info)
{
	int	i;

	i = 0;
	while (i < NULL_LENGTH)
	{
		if (champ_info[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

int				check_registr(t_carriage *car, int reg)
{
	if (reg >= 1 && reg <= 16)
		return (1);
	else
	{
		car->position += car->step;
		car->opcode = 0;
		return (0);
	}
}
