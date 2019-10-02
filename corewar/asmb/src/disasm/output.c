/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:58:48 by tdontos-          #+#    #+#             */
/*   Updated: 2019/09/07 16:58:51 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/disasm.h"

void	section(void)
{
	check_magic();
	ft_putstr_fd(".name \"", g_fd_new);
	input_code(PROG_NAME_LENGTH);
	ft_putstr_fd("\"\n", g_fd_new);
	skip_bytes(4);
	ft_putstr_fd(".comment \"", g_fd_new);
	input_code(COMMENT_LENGTH);
	ft_putstr_fd("\"\n", g_fd_new);
	while (read_cmd() == 1)
		continue ;
}

void	input_code(int max_size)
{
	char	buf;
	int		i;

	i = 0;
	while (read(g_fd_read, &buf, 1) > 0 && i <= max_size)
	{
		if (buf != 0)
			ft_putchar_fd(buf, g_fd_new);
		i++;
	}
}

int		read_cmd(void)
{
	char	buf;
	char	*res;
	int		index;
	int		accept;

	while ((accept = read(g_fd_read, &buf, 1)) > 0)
	{
		if (buf != 0)
			break ;
	}
	if (accept <= 0)
		return (0);
	index = (int)buf - 1;
	ft_putchar_fd('\t', g_fd_new);
	res = ft_strjoin(g_op_tab[index].name, " ");
	ft_putstr_fd(res, g_fd_new);
	ft_strdel(&res);
	read_args(g_op_tab[index].nb_arg, index, count_args(index));
	return (1);
}

void	read_args(int count, int index, int *args)
{
	int		i;
	int		size;

	i = -1;
	while (++i < count)
	{
		if (args[i] == T_REG)
		{
			ft_putchar_fd('r', g_fd_new);
			size = 1;
		}
		else if (args[i] == T_DIR)
		{
			ft_putchar_fd('%', g_fd_new);
			size = g_op_tab[index].label == 0 ? 4 : 2;
		}
		else
			size = 2;
		ft_putnbr_fd(digit_arg(size), g_fd_new);
		if (i + 1 < count)
			ft_putstr_fd(", ", g_fd_new);
	}
	free(args);
	ft_putchar_fd('\n', g_fd_new);
}

int		digit_arg(int size)
{
	t_byte	buf;

	buf.ints = 0;
	read(g_fd_read, buf.chars, size);
	buf.ints = reverse(buf.ints, size);
	if (buf.ints >= 0x7FFF && size == 2)
		buf.ints = ~(buf.ints ^ 0xFFFF);
	return (buf.ints);
}
