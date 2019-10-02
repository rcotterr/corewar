/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_type1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:25:11 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/12 16:20:42 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

char		*str3(int i)
{
	char	*ret;

	if (!(ret = (char *)ft_memalloc(sizeof(char) * 4)))
		return (ret);
	ret[0] = i / 100 + 48;
	ret[1] = (i % 100) / 10 + 48;
	ret[2] = i % 10 + 48;
	ret[3] = '\0';
	return (ret);
}

void		direr(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\"\n", 2);
}

static void	zh0(t_type type)
{
	if (type.type == DIR)
	{
		if (type.str[0] == ':')
			ft_putstr_fd("DIRECT_LABEL \"%", 2);
		else
			ft_putstr_fd("DIRECT \"%", 2);
		direr(type.str);
	}
	if (type.type == STR)
	{
		ft_putstr_fd("STRING \"\"", 2);
		ft_putstr_fd(type.str, 2);
		ft_putstr_fd("\"\"\n", 2);
	}
	if (type.type == LABEL)
	{
		ft_putstr_fd("LABEL \"", 2);
		direr(type.str);
	}
	if (type.type == INS)
	{
		ft_putstr_fd("INSTRUCTION \"", 2);
		direr(type.str);
	}
}

static void	hz1(t_type type)
{
	if (type.type == INDIR)
	{
		if (type.str[0] == ':')
			ft_putstr_fd("INDIRECT_LABEL \"", 2);
		else
			ft_putstr_fd("INDIRECT \"", 2);
		direr(type.str);
	}
	if (type.type == REG)
	{
		ft_putstr_fd("REGISTER \"", 2);
		direr(type.str);
	}
	if (type.type == SEP)
	{
		ft_putstr_fd("SEPARATOR \"", 2);
		direr(type.str);
	}
}

int			synerr(t_type type)
{
	char	*del;

	ft_putstr_fd("Syntax error at token [TOKEN][", 2);
	ft_putstr_fd((del = str3(type.i)), 2);
	ft_strdel(&del);
	ft_putchar_fd(':', 2);
	ft_putstr_fd((del = str3(type.j)), 2);
	ft_strdel(&del);
	ft_putstr_fd("] ", 2);
	zh0(type);
	hz1(type);
	if (type.type == CMD)
	{
		ft_putstr_fd("COMMAND_NAME \"", 2);
		direr(type.str);
	}
	type.type == NL ? ft_putstr_fd("ENDLINE\n", 2) : 1;
	return (0);
}
