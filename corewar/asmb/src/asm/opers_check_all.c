/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_check_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:57:19 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/15 14:59:25 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

t_type	*ch_open_str(long mod, char **str, t_type **ty)
{
	if (mod)
	{
		ft_strdel(str);
		open_str();
		deltype((*ty), (*ty)[0].count);
		return (((*ty) = 0));
	}
	return (*ty);
}

int		ch_all(t_type **ty, int i, int *j, char **l)
{
	if ((l[i][(*j)] == DIRECT_CHAR && !(ch_dir(ty, i, j, l))) ||
			((l[i][(*j)] == LABEL_CHAR || (l[i][(*j)] >= '0' &&
										l[i][(*j)] <= '9') ||
			l[i][(*j)] == '-') && !(ch_indir(ty, i, j, l))) ||
			(islchar(l[i][(*j)]) && !(ch_label(ty, i, j, l))) ||
			(l[i][(*j)] == 'r' && !(ch_reg(ty, i, j, l))) ||
			(islchar(l[i][(*j)]) && !(ch_ins(ty, i, j, l))) ||
			((l[i][(*j)] == ' ' || l[i][(*j)] == '\t')))
		return (0);
	return (1);
}

int		cadd(long mod, char **str)
{
	if (mod)
		(*str) = addcstr(*str, '\n');
	return (1);
}

t_type	*del_type(t_type **ty)
{
	deltype((*ty), (*ty)[0].count);
	*ty = 0;
	return (*ty);
}

t_type	*set_arr(int *i, long *mod)
{
	t_type	*ret;

	(*i) = -1;
	(*mod) = 0;
	ret = NULL;
	ret = addtype(ret, "NL", NL, 0);
	return (ret);
}
