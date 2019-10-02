/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_is_type2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:54:57 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/15 15:55:02 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

char	*isreg(char *str, int x)
{
	char	*ret;

	ret = NULL;
	if (!(ret = (char *)ft_memalloc(sizeof(char))))
		return (ret);
	if (str[x + 1] && str[x + 1] >= '0' && str[x + 1] <= '9'
			&& isvalidend(str[x + 2]))
	{
		ret = addcstr(ret, 'r');
		ret = addcstr(ret, str[x + 1]);
		return (ret);
	}
	if (str[x + 1] && str[x + 1] >= '0' && str[x + 1] <= '9'
			&& str[x + 2] && str[x + 2] >= '0' && str[x + 2] <= '9'
			&& isvalidend(str[x + 3]))
	{
		ret = addcstr(ret, 'r');
		ret = addcstr(ret, str[x + 1]);
		ret = addcstr(ret, str[x + 2]);
		return (ret);
	}
	ft_strdel(&ret);
	return (ret);
}

char	*isdir(char *str, int x)
{
	char	*ret;

	ret = NULL;
	if (!(ret = (char *)ft_memalloc(sizeof(char))))
		return (ret);
	if (str[++x] && str[x] == LABEL_CHAR)
	{
		ret = addcstr(ret, ':');
		while (str[++x] && islchar(str[x]))
			ret = addcstr(ret, str[x]);
		return (ret);
	}
	x--;
	while (str[++x] && ((str[x] >= '0' && str[x] <= '9')
				|| (ft_strlen(ret) == 0 && str[x] == '-')))
		ret = addcstr(ret, str[x]);
	if (ft_strlen(ret) < 1)
		ft_strdel(&ret);
	return (ret);
}

char	*isindir(char *str, int x)
{
	char	*ret;
	int		f;

	ret = NULL;
	if (!(ret = (char *)ft_memalloc(sizeof(char))))
		return (ret);
	if (str[x] && str[x] == LABEL_CHAR)
	{
		ret = addcstr(ret, ':');
		while (str[++x] && islchar(str[x]))
			ret = addcstr(ret, str[x]);
		if (ft_strlen(ret) < 2)
			ft_strdel(&ret);
		return (ret);
	}
	f = 0;
	if (str[x] == '-' && ++f)
		ret = addcstr(ret, str[x++]);
	x--;
	while (str[++x] && (str[x] >= '0' && str[x] <= '9'))
		ret = addcstr(ret, str[x]);
	if (ft_strlen(ret) < (size_t)1 + f || !isvalidend(str[x]))
		ft_strdel(&ret);
	return (ret);
}

char	*isins(char *str, int x)
{
	char	*ret;

	ret = NULL;
	if (!(ret = (char *)ft_memalloc(sizeof(char))))
		return (ret);
	x--;
	while (str[++x] && islchar(str[x]))
		ret = addcstr(ret, str[x]);
	if (isvalidend(str[x]))
		return (ret);
	ft_strdel(&ret);
	return (ret);
}

long	itol(int i, int j)
{
	long	x;

	x = 0;
	x += i + 1;
	x <<= 32;
	x += j + 1;
	return (x);
}
