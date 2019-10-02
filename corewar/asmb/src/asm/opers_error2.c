/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:30:54 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/25 19:12:38 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int	inval_par(int ind, char *ins, char type, t_type types)
{
	if (type != DIR && type != REG && type != INDIR)
		return (synerr(types));
	ft_putstr_fd("Invalid parameter ", 2);
	ft_putnbr_fd(ind, 2);
	ft_putstr_fd(" type ", 2);
	if (type == DIR)
		ft_putstr_fd("direct for instruction ", 2);
	if (type == REG)
		ft_putstr_fd("register for instruction ", 2);
	if (type == INDIR)
		ft_putstr_fd("indirect for instruction ", 2);
	ft_putstr_fd(ins, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	usage(char *name)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(" <sourcefile.s> [-h]\n -h : to create a file", 2);
	ft_putstr_fd(" in the current directory\n", 2);
	return (0);
}

int	lexical_er(int x, int i)
{
	i++;
	x++;
	ft_putstr_fd("Lexical error at [", 2);
	ft_putnbr_fd(x, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(i, 2);
	ft_putendl_fd("]", 2);
	return (0);
}

int	open_str(void)
{
	ft_putstr_fd("Not a closed STRING\n", 2);
	return (0);
}
