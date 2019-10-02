/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:53:36 by tdontos-          #+#    #+#             */
/*   Updated: 2019/09/07 16:53:40 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/disasm.h"

unsigned int	reverse(unsigned int x, int cnt)
{
	if (cnt == 1)
		return (x);
	x = (x & 0x00FF00FF) << 8 | (x & 0xFF00FF00) >> 8;
	if (cnt == 4)
		x = (x & 0x0000FFFF) << 16 | (x & 0xFFFF0000) >> 16;
	return (x);
}

int				check_magic(void)
{
	t_byte	byte;

	read(g_fd_read, byte.chars, 4);
	byte.ints = reverse(byte.ints, 4);
	if ((int)byte.ints == COREWAR_EXEC_MAGIC)
		return (1);
	valid_error(1);
	return (0);
}

void			skip_bytes(int count)
{
	char	buf;
	int		i;

	i = 0;
	while (read(g_fd_read, &buf, 1) > 0 && i <= count)
		i++;
}

void			valid_error(int code)
{
	if (code == 1)
		ft_putstr("Error: missing EXEC MAGIC");
	exit(1);
}

int				*count_args(int index)
{
	unsigned char	buf;
	int				*res;
	int				i;

	if (g_op_tab[index].nb_arg <= 1)
	{
		res = (int *)ft_memalloc(sizeof(int));
		res[0] = g_op_tab[index].args[0];
		return (res);
	}
	res = (int *)ft_memalloc(sizeof(int) * g_op_tab[index].nb_arg);
	i = 3;
	read(g_fd_read, &buf, 1);
	while (--i >= 0)
	{
		buf = buf >> 2;
		res[i] = buf & 0x00000003;
	}
	return (res);
}
