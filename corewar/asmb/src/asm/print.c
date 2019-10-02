/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:48:12 by tdontos-          #+#    #+#             */
/*   Updated: 2019/08/03 18:48:14 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

/*
** this function makes bincode and writes it in the file
*/

int		make_bin(char *line, int size, int nll)
{
	int		i;

	if (size == 0)
		return (0);
	i = -1;
	while (++i < size)
		ft_putchar_fd(line[i], g_fd_new);
	while (++i <= size + nll)
		ft_putchar_fd(0, g_fd_new);
	return (1);
}

/*
** this function write error and exit programm
*/

void	valid_error(int code, int size)
{
	if (code == 1)
		ft_putstr_fd("wrong file", 2);
	if (code == 2)
	{
		ft_putstr_fd("Champion ", 2);
		ft_putstr_fd(size == COMMENT_LENGTH ? "comment" : "name", 2);
		ft_putstr_fd(" too long (Max length ", 2);
		ft_putnbr_fd(size, 2);
		ft_putstr_fd(")", 2);
	}
	if (code == 3)
	{
		ft_putstr_fd("Syntax error - unexpected end of input", 2);
		ft_putstr_fd("(Perhaps you forgot to end with a newline ?)", 2);
	}
	ft_putchar_fd('\n', 2);
	exit(1);
}

void	print_magic(void)
{
	t_byte	magic;

	magic.ints = COREWAR_EXEC_MAGIC;
	ft_putchar_fd(magic.chars[3], g_fd_new);
	ft_putchar_fd(magic.chars[2], g_fd_new);
	ft_putchar_fd(magic.chars[1], g_fd_new);
	ft_putchar_fd(magic.chars[0], g_fd_new);
}

void	end_programm(char **nametype, t_type **file, t_header **head, int count)
{
	ft_putstr_fd("Writing output program to ", 1);
	ft_putstr_fd(*nametype, 1);
	ft_putchar_fd('\n', 1);
	free(*nametype);
	close(g_fd_read);
	close(g_fd_new);
	free(*head);
	deltype(*file, count);
}

t_byte	type_date(t_byte args, int *size, t_cmd *cmd, t_type file)
{
	if (file.type == REG)
	{
		args.chars[0] = ft_atoi(&file.str[1]);
		*size = 1;
	}
	else
	{
		if (ft_isdigit(file.str[0]) == 0 && file.str[0] != '-')
			args.ints = reverse(search_lbl_next(file.str, cmd), *size);
		else
			args.ints = reverse(ft_atoi(file.str), *size);
		*size = 2;
	}
	return (args);
}
