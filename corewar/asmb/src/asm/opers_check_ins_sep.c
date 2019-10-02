/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_check_ins_sep.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:49:45 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/15 14:59:38 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int		ch_ins(t_type **types, int i, int *j, char **list)
{
	char	*str;

	if ((str = isins(list[i], (*j))))
	{
		(*types) = addtype((*types), str, INS, itol(i, (*j)));
		(*j) += ft_strlen(str) - 1;
		ft_strdel(&str);
		return (0);
	}
	return (1);
}

int		ch_com(t_type **types, int i, int *j, char **list)
{
	if (!com(list[i], (*j)))
	{
		deltype((*types), (*types)[0].count);
		lexical_er(i, (*j));
		return (0);
	}
	else
		(*types) = addtype((*types), com(list[i], (*j)), CMD, itol(i, (*j)));
	(*j) += ft_strlen(com(list[i], (*j))) - 1;
	return (1);
}

int		end_str(long ij, char **list, long *mod, char **str)
{
	if (!(*mod) && list[inttolong(0, ij)][inttolong(1, ij)] == '\"')
	{
		(*str) = (char *)ft_memalloc(sizeof(char));
		(*mod) = itol(inttolong(0, ij), inttolong(1, ij));
		return (0);
	}
	lexical_er(inttolong(0, ij), inttolong(1, ij));
	return (1);
}

int		nl(long mod, t_type **types, int i, int j)
{
	if (!mod)
	{
		if ((*types)[(*types)[0].count - 1].type == NL &&
				(((*types)[(*types)[0].count - 1].i = i + 1)))
			(*types)[(*types)[0].count - 1].j = j + 1;
		else
			(*types) = addtype((*types), "NL", NL, itol(i, j));
	}
	return (1);
}

int		ch_sep(long mod, long ij, t_type **types, char **list)
{
	if (!mod && list[inttolong(0, ij)][inttolong(1, ij)] == SEPARATOR_CHAR &&
			(((*types) = addtype((*types), ",",
								SEP, itol(inttolong(0, ij),
									inttolong(1, ij)))) || 1))
		return (0);
	return (1);
}
