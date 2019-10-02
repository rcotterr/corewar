/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_val_label.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:56:48 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/25 19:57:42 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int		label_dir(char *s2, char *s1)
{
	char	rs1[ft_strlen(s1)];
	char	rs2[ft_strlen(s2)];
	int		i;

	i = -1;
	while (s1[++i + 1])
		rs1[i] = s1[i + 1];
	rs1[i] = '\0';
	i = -1;
	while (++i < (int)ft_strlen(s2) - 1)
		rs2[i] = s2[i];
	rs2[i] = '\0';
	if (ft_strequ(rs1, rs2))
		return (1);
	return (0);
}

int		double_label(t_type *t)
{
	int		i;
	int		j;
	char	f;

	f = 1;
	i = -1;
	while (++i < t[0].count && ((j = -1) || 1))
	{
		if ((t[i].type == DIR && t[i].str[0] == ':')
				|| (t[i].type == INDIR && t[i].str[0] == ':'))
			f = 0;
		while (++j < t[0].count)
		{
			if (i == j)
				continue ;
			if (t[i].type == LABEL && t[j].type == LABEL
					&& ft_strequ(t[i].str, t[j].str))
				return (!double_lab(t, i, j));
			if (f == 0 && t[j].type == LABEL && label_dir(t[j].str, t[i].str))
				f = 1;
		}
		if (!f)
			return (!no_dirlabel(t[i]));
	}
	return (0);
}
