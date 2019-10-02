/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:57:05 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/25 20:05:36 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int		inval_ins(t_type type)
{
	char	*str;

	ft_putstr_fd("Invalid instruction at token [TOKEN][", 2);
	ft_putstr_fd((str = str3(type.i)), 2);
	ft_putchar_fd(':', 2);
	ft_strdel(&str);
	ft_putstr_fd((str = str3(type.j)), 2);
	ft_strdel(&str);
	ft_putstr_fd("] ", 2);
	if (type.type == INS)
	{
		ft_putstr_fd("INSTRUCTION \"", 2);
		direr(type.str);
	}
	return (0);
}

int		double_lab(t_type *types, int i, int j)
{
	char	*ret;

	ft_putstr_fd("Duplicate label \"", 2);
	ft_putstr_fd(types[i].str, 2);
	ft_putstr_fd("\" [TOKEN][", 2);
	ft_putstr_fd((ret = str3(types[i].i)), 2);
	ft_strdel(&ret);
	ft_putstr_fd(":", 2);
	ft_putstr_fd((ret = str3(types[i].j)), 2);
	ft_strdel(&ret);
	ft_putstr_fd("] and \"", 2);
	ft_putstr_fd(types[j].str, 2);
	ft_putstr_fd("\" [TOKEN][", 2);
	ft_putstr_fd((ret = str3(types[j].i)), 2);
	ft_strdel(&ret);
	ft_putstr_fd(":", 2);
	ft_putstr_fd((ret = str3(types[j].j)), 2);
	ft_strdel(&ret);
	ft_putstr_fd("]\n", 2);
	return (0);
}

char	*get_label(char *str)
{
	char	*ret;
	int		i;

	if (!(ret = (char *)ft_memalloc(sizeof(char) * ft_strlen(str))))
		return (ret);
	i = -1;
	while (str[++i + 1])
		ret[i] = str[i + 1];
	return (ret);
}

int		no_dirlabel(t_type types)
{
	char	*ret;

	ret = get_label(types.str);
	ft_putstr_fd("No such label ", 2);
	ft_putstr_fd(ret, 2);
	ft_strdel(&ret);
	ft_putstr_fd(" while attempting to dereference token [TOKEN][", 2);
	ft_putstr_fd((ret = str3(types.i)), 2);
	ft_strdel(&ret);
	ft_putstr_fd(":", 2);
	ft_putstr_fd((ret = str3(types.j)), 2);
	ft_strdel(&ret);
	if (types.type == DIR)
		ft_putstr_fd("] DIRECT_LABEL \"%", 2);
	if (types.type == INDIR)
		ft_putstr_fd("] INDIRECT_LABEL \"%", 2);
	ft_putstr_fd(types.str, 2);
	ft_putstr_fd("\"\n", 2);
	return (0);
}

int		null_as(t_type types)
{
	char	*del;

	ft_putstr_fd("Syntax error at token [TOKEN][", 2);
	ft_putstr_fd((del = str3(types.i + 1)), 2);
	ft_strdel(&del);
	ft_putchar_fd(':', 2);
	ft_putstr_fd((del = str3(1)), 2);
	ft_strdel(&del);
	ft_putstr_fd("] END \"(null)\"\n", 2);
	return (0);
}
