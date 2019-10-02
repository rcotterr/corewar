/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_val5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:51:27 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/15 16:46:21 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

char	*delcomment(char *str)
{
	char	*ret;
	int		x;
	int		i;

	x = -1;
	while (str[++x] && str[x] != COMMENT_CHAR
			&& str[x] != ALT_COMMENT_CHAR)
		;
	if (!x || !(ret = (char *)malloc(sizeof(char) * (x + 1))))
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (++i < x)
		ret[i] = str[i];
	ret[i] = '\0';
	free(str);
	return (ret);
}

long	itoln(int i, int j)
{
	long	x;

	x = 0;
	x += i;
	x <<= 32;
	x += j;
	return (x);
}

t_type	*settype(char **l, int i, int j, long mod)
{
	t_type	*ty;
	char	*str;

	ty = set_arr(&i, &mod);
	while (nl(mod, &ty, i, j) && l[++i] && ((j = -1) || 1) && cadd(mod, &str))
		while (l[i][++j])
		{
			if (!(add_c_str(&ty, l[i][j], &mod, &str)))
				continue ;
			if (l[i][j] == COMMENT_CHAR || l[i][j] == ALT_COMMENT_CHAR)
				break ;
			if (!(ch_sep(mod, itoln(i, j), &ty, l)))
				continue ;
			if (!mod)
				if (!(ch_all(&ty, i, &j, l)) || l[i][j] == '.')
				{
					if (l[i][j] == '.' && !(ch_com(&ty, i, &j, l)))
						return ((ty = 0));
					continue ;
				}
			if (!(end_str(itoln(i, j), l, &mod, &str)))
				continue ;
			return (del_type(&ty));
		}
	return (ch_open_str(mod, &str, &ty));
}

int		valid_id_arg(int ins, int ind, t_type types)
{
	char	type;
	char	ttype;

	ttype = 0;
	if (ind >= g_op_tab[ins].nb_arg)
		return (0);
	type = g_op_tab[ins].args[ind];
	if (types.type == REG)
		ttype = T_REG;
	if (types.type == DIR)
		ttype = T_DIR;
	if (types.type == INDIR)
		ttype = T_IND;
	if (type & ttype)
		return (1);
	return (0);
}

char	get_code(t_type type)
{
	int	i;

	i = -1;
	while (g_op_tab[++i].nb_arg != 0)
		if (ft_strequ(type.str, g_op_tab[i].name))
			return (i + 5);
	return (0);
}
