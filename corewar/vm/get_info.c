/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:55:51 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/14 14:25:43 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ_info		get_champ_info(int fd)
{
	t_champ_info	champ_info;
	int				max_info_size;

	max_info_size = COREWAR_MAGIC_LENGTH + PROG_NAME_LENGTH + NULL_LENGTH +
		COREWAR_SIZE_LENGTH + COMMENT_LENGTH + NULL_LENGTH + CHAMP_MAX_SIZE;
	champ_info.info = ft_memalloc(max_info_size + 1);
	champ_info.len = read(fd, champ_info.info, max_info_size + 1);
	if (champ_info.len == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		free(champ_info.info);
		champ_info.info = NULL;
		exit(-1);
	}
	if (champ_info.len > max_info_size)
	{
		ft_putendl_fd("Champ code is bigger than CHAMP_MAX_SIZE", 2);
		free(champ_info.info);
		champ_info.info = NULL;
		exit(-1);
	}
	return (champ_info);
}

char				*get_champ_name(char *champ_info)
{
	int		len;
	char	*name;

	len = 0;
	while (champ_info[len])
		len++;
	name = ft_memalloc(len + 1);
	ft_strncpy(name, champ_info, len);
	return (name);
}

char				*get_champ_comment(char *champ_info)
{
	int		len;
	char	*comment;

	len = 0;
	while (champ_info[len])
		len++;
	comment = ft_memalloc(len + 1);
	ft_strncpy(comment, champ_info, len);
	return (comment);
}

unsigned char		*get_champ_exec_code(t_champ_info champ_info)
{
	char	*exec_code;
	int		i;
	int		j;

	j = 0;
	i = COREWAR_MAGIC_LENGTH + PROG_NAME_LENGTH + NULL_LENGTH +
		COREWAR_SIZE_LENGTH + COMMENT_LENGTH + NULL_LENGTH;
	exec_code = ft_memalloc(champ_info.len - i);
	while (i < champ_info.len)
	{
		exec_code[j] = (champ_info.info)[i];
		i++;
		j++;
	}
	return ((unsigned char *)exec_code);
}

int					get_champ_size(char *champ_info)
{
	int				i;
	int				size;
	union u_byte	byte;

	i = 0;
	byte.ints = 0;
	while (i < COREWAR_SIZE_LENGTH)
	{
		byte.chars[i] = champ_info[i];
		i++;
	}
	size = reverse(byte.ints, COREWAR_SIZE_LENGTH);
	return (size);
}
