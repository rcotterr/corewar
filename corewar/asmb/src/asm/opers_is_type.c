/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_is_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:54:40 by kmurch            #+#    #+#             */
/*   Updated: 2019/09/15 16:09:14 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

char	*com(char *str, int x)
{
	int		i;
	char	f;

	i = -1;
	f = 0;
	while (NAME_CMD_STRING[++i])
		if (NAME_CMD_STRING[i] != str[i + x])
			f = 1;
	if (!f)
		return (NAME_CMD_STRING);
	i = -1;
	f = 0;
	while (COMMENT_CMD_STRING[++i])
		if (COMMENT_CMD_STRING[i] != str[i + x])
			f = 1;
	if (!f)
		return (COMMENT_CMD_STRING);
	return (NULL);
}

char	*addcstr(char *str, char c)
{
	char	*ret;
	int		x;
	int		len;

	len = ft_strlen(str);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 2))))
	{
		ft_strdel(&str);
		return (str);
	}
	x = -1;
	while (str[++x])
		ret[x] = str[x];
	ret[x] = c;
	ret[x + 1] = '\0';
	ft_strdel(&str);
	return (ret);
}

int		islchar(char c)
{
	int	x;

	x = -1;
	while (LABEL_CHARS[++x])
		if (c == LABEL_CHARS[x])
			return (1);
	return (0);
}

char	*islabel(char *str, int x)
{
	char	*ret;

	if (!(ret = (char *)ft_memalloc(sizeof(char))))
		return (ret);
	x--;
	while (str[++x] && islchar(str[x]))
		ret = addcstr(ret, str[x]);
	if (str[x] && str[x] == LABEL_CHAR)
	{
		ret = addcstr(ret, ':');
		return (ret);
	}
	ft_strdel(&ret);
	return (ret);
}

int		isvalidend(char c)
{
	if (c == ' ' || c == '\t' || c == '\0'
			|| c == COMMENT_CHAR || c == ALT_COMMENT_CHAR
			|| c == DIRECT_CHAR || c == SEPARATOR_CHAR
			|| c == '\"' || c == '-' || c == '.')
		return (1);
	return (0);
}
