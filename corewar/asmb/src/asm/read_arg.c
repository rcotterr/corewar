/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 20:10:13 by tdontos-          #+#    #+#             */
/*   Updated: 2019/08/07 20:10:14 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

char			arg_sums(char bits, int type)
{
	bits = bits | type;
	bits = bits << 2;
	return (bits);
}

int				write_arg(t_type *file, int tdir, t_cmd *cmd)
{
	int		i;
	t_byte	args;
	int		size;

	i = -1;
	while (file[++i].type != NL)
	{
		if (file[i].type == INS)
			continue ;
		args.ints = 0;
		size = -1;
		if (file[i].type == DIR)
		{
			if (ft_isdigit(file[i].str[0]) == 0 && file[i].str[0] != '-')
				args.ints = reverse(search_lbl_next(file[i].str, cmd), tdir);
			else
				args.ints = reverse(ft_atoi(&file[i].str[0]), tdir);
			size = tdir;
		}
		else if (file[i].type == REG || file[i].type == INDIR)
			args = type_date(args, &size, cmd, file[i]);
		if (size != -1)
			make_bin((char *)args.chars, size, 0);
	}
	return (i);
}

int				search_lbl_prev(char *str, t_cmd *cmd)
{
	t_cmd	*tmp;
	int		size;

	size = 0;
	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->lbl != NULL && ft_strcmp(tmp->lbl, (str + 1)) == 0)
			return (size);
		tmp = tmp->prev;
		if (tmp != NULL)
			size -= tmp->size;
	}
	return (0);
}

int				search_lbl_next(char *str, t_cmd *cmd)
{
	t_cmd	*tmp;
	int		size;

	if (cmd == NULL)
		return (0);
	size = 0;
	tmp = cmd;
	while (tmp->next != NULL)
	{
		if (tmp->lbl != NULL && ft_strcmp(tmp->lbl, (str + 1)) == 0)
			return (size);
		size += tmp->size;
		tmp = tmp->next;
	}
	return (search_lbl_prev(str, cmd));
}

unsigned int	reverse(unsigned int x, int cnt)
{
	x = (x & 0x00FF00FF) << 8 | (x & 0xFF00FF00) >> 8;
	if (cnt == 4)
		x = (x & 0x0000FFFF) << 16 | (x & 0xFFFF0000) >> 16;
	return (x);
}
