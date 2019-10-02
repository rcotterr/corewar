/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 18:49:31 by tdontos-          #+#    #+#             */
/*   Updated: 2019/08/04 18:49:33 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int		pars_lbl(t_type *file, t_cmd *cmd, int max, int pos)
{
	int		index;

	while (file->type == NL && pos < max)
	{
		pos++;
		++file;
	}
	if (pos >= max)
		return (0);
	index = output_oper(file->str);
	if (index == -1)
		return (0);
	return (pars_arg(file, index, cmd));
}

int		output_oper(char *line)
{
	int		i;

	i = -1;
	if (line == NULL)
		return (-1);
	while (++i < REG_NUMBER)
	{
		if (ft_strcmp(line, g_op_tab[i].name) == 0)
			return (i);
	}
	return (-1);
}

int		pars_arg(t_type *file, int index, t_cmd *cmd)
{
	int		i;
	char	bin;

	ft_putchar_fd((char)index + 1, g_fd_new);
	i = -1;
	bin = 0;
	while (file[++i].type != NL)
	{
		if (file[i].type == REG)
			bin = arg_sums(bin, T_REG);
		else if (file[i].type == DIR)
			bin = arg_sums(bin, T_DIR);
		else if (file[i].type == INDIR)
			bin = arg_sums(bin, 3);
	}
	bin = bin << (3 - g_op_tab[index].nb_arg) * 2;
	if (g_op_tab[index].nb_arg > 1)
		make_bin(&bin, 1, 0);
	if (ft_strcmp(g_op_tab[index].name, "aff") == 0)
		make_bin(&bin, 1, 0);
	return (write_arg(file, g_op_tab[index].label == 0 ? 4 : 2, cmd));
}

int		check_nl(char *name, int fd)
{
	char	buf[2];
	int		nl;

	nl = 0;
	close(fd);
	fd = open(name, O_RDONLY);
	while (read(fd, buf, 1) > 0)
	{
		buf[1] = '\0';
		if (ft_isspace(buf[0]) == 0)
			nl = 0;
		if (buf[0] == '\n')
			nl = 1;
	}
	if (nl == 0)
		return (0);
	return (1);
}
