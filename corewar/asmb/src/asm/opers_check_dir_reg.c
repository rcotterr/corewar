/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_check_dir_reg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:47:44 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/25 16:02:14 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int	add_c_str(t_type **types, char c, long *mod, char **str)
{
	if ((*mod) && c == '\"')
	{
		(*types) = addtype((*types), (*str), STR, (*mod));
		ft_strdel(str);
		(*mod) = 0;
		return (0);
	}
	if ((*mod))
	{
		(*str) = addcstr((*str), c);
		return (0);
	}
	return (1);
}

int	ch_dir(t_type **types, int i, int *j, char **list)
{
	char	*str;

	if ((str = isdir(list[i], (*j))))
	{
		(*types) = addtype((*types), str, DIR, itol(i, (*j)));
		(*j) += ft_strlen(str);
		ft_strdel(&str);
		return (0);
	}
	return (1);
}

int	ch_indir(t_type **types, int i, int *j, char **list)
{
	char	*str;

	if ((str = isindir(list[i], (*j))))
	{
		(*types) = addtype((*types), str, INDIR, itol(i, (*j)));
		(*j) += ft_strlen(str) - 1;
		ft_strdel(&str);
		return (0);
	}
	return (1);
}

int	ch_label(t_type **types, int i, int *j, char **list)
{
	char	*str;

	if ((str = islabel(list[i], (*j))))
	{
		(*types) = addtype((*types), str, LABEL, itol(i, (*j)));
		(*j) += ft_strlen(str) - 1;
		ft_strdel(&str);
		return (0);
	}
	return (1);
}

int	ch_reg(t_type **types, int i, int *j, char **list)
{
	char	*str;

	if ((str = isreg(list[i], (*j))))
	{
		(*types) = addtype((*types), str, REG, itol(i, (*j)));
		(*j) += ft_strlen(str) - 1;
		ft_strdel(&str);
		return (0);
	}
	return (1);
}
