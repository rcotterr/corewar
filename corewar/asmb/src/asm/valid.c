/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:30:30 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/15 17:03:17 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int		hz1(t_type type, char *c, char t)
{
	if ((*c == 0 || *c == 2) && !(t == CMD || t == NL))
		return (synerr(type));
	if ((*c == 1 || *c == 3) && t != STR)
		return (synerr(type));
	if (t == 1 && ++(*c))
		return (1);
	if (t == 9 && ++(*c))
		return (1);
	if ((*c) == 4 && t != NL && t != INS && t != LABEL)
		return (synerr(type));
	if ((*c) == 4 && t == INS)
	{
		if (!((*c) = get_code(type)))
			return (inval_ins(type));
		return (1);
	}
	return (2);
}

int		zh1(t_type type, char t, char *c, char *p)
{
	if (t == NL && (*p) == g_op_tab[(*c) - 5].nb_arg + 3 && ((*c) = 4)
			&& (((*p) = 0) || 1))
		return (1);
	if (t != SEP)
	{
		if ((*p) < g_op_tab[(*c) - 5].nb_arg + 3 && t == NL)
		{
			ft_putstr_fd("Invalid parameter count for instruction ", 2);
			ft_putstr_fd(g_op_tab[(*c) - 5].name, 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
		return (synerr(type));
	}
	(*p) -= 3;
	return (1);
}

int		hz0(t_type type, char t, char *c, char *p)
{
	int	mody;

	if ((*c) == 4 && t == LABEL && (((*c) = -1) || 1))
		return (1);
	if ((*c) == -1 && t != INS && t != NL && t != LABEL)
		return (synerr(type));
	else
	{
		if (t == INS && (*c) == -1)
			(*c) = 4;
	}
	if (!(mody = hz1(type, c, t)))
		return (0);
	if (mody == 1)
		return (1);
	if ((*c) >= 5 && (*c) <= 21 && (*p) >= 4)
		return (zh1(type, t, c, p));
	if ((*c) >= 5 && (*c) <= 21)
	{
		if (!(valid_id_arg((*c) - 5, (*p), type)))
			return (inval_par((*p), g_op_tab[(*c) - 5].name, type.type, type));
		(*p) += 4;
	}
	return (1);
}

int		valid_logic(t_type *ty)
{
	char	c;
	int		x;
	char	t;
	char	p;

	c = 0;
	x = -1;
	p = 0;
	while (++x < ty[0].count && ((t = ty[x].type) || 1))
	{
		if (hz0(ty[x], t, &c, &p))
			continue ;
		else
			return (0);
	}
	if (c != -1 && c < 4)
		return (null_as(ty[ty[0].count - 1]));
	return (1);
}

t_type	*valid(char **list)
{
	t_type	*types;
	int		i;
	int		j;
	long	mod;

	i = -1;
	j = -1;
	mod = 0;
	if (!(types = settype(list, i, j, mod)))
	{
		dellist(list);
		return ((types = 0));
	}
	dellist(list);
	if (!((valid_logic(types) && !double_label(types))))
	{
		deltype(types, types[0].count);
		return ((types = 0));
	}
	return (types);
}
