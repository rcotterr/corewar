/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:08:46 by tdontos-          #+#    #+#             */
/*   Updated: 2019/09/25 19:01:31 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

t_type	*read_file(char *name)
{
	char	*line;
	char	**list;
	int		fd;

	list = NULL;
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Can't read source file ", 2);
		ft_putendl_fd(name, 2);
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0)
	{
		if (!(list = addlist(list, line)))
		{
			dellist(list);
			free(line);
			return (NULL);
		}
		free(line);
	}
	if (check_nl(name, fd) == 0)
		valid_error(3, 0);
	return (valid(list));
}

void	check_file(t_type *file, t_cmd *cmd)
{
	int		i;
	int		res;

	i = -1;
	while (++i != file[0].count)
	{
		if (file[i].type == NL)
			continue ;
		else if (file[i].type == LABEL || file[i].type == INS)
		{
			res = pars_lbl(&file[file[i].type == LABEL ? i + 1 : i], cmd,
							file[0].count, i);
			if (res != 0)
				cmd = cmd == NULL ? NULL : cmd->next;
			while (cmd != NULL && cmd->size == 0)
				cmd = cmd == NULL ? NULL : cmd->next;
			i += res;
		}
		else if (file[i].type == CMD)
			continue ;
	}
}

int		check_line(t_header *head, t_type *file)
{
	t_byte	size;

	if (ft_strstr(file->str, NAME_CMD_STRING) != NULL)
	{
		pars_line(head->prog_name, PROG_NAME_LENGTH, file);
		size.ints = head->prog_size;
		size.ints = reverse(size.ints, 4);
		make_bin((char *)size.chars, 4, 0);
	}
	else if (ft_strstr(file->str, COMMENT_CMD_STRING) != NULL)
		pars_line(head->comment, COMMENT_LENGTH, file);
	return (1);
}

void	pars_line(char *line, int size, t_type *file)
{
	int		i;
	char	*tmp;

	i = -1;
	while (file->type != STR)
		++file;
	tmp = file->str;
	if (ft_strlen(tmp) > (size_t)size)
		valid_error(2, size);
	while (tmp[++i] != '\0')
		line[i] = tmp[i];
	while (++i < size)
		line[i] = '\0';
	make_bin(line, size, 4);
}

int		repeat_lbl(t_cmd *cmd, t_type *file, int max)
{
	int		i;
	int		lbl;

	lbl = 0;
	i = 0;
	while (i < max && file[i].type != INS)
	{
		if (file[i].type == LABEL)
			lbl++;
		if (lbl == 2)
		{
			cmd->size = 0;
			return (-1);
		}
		i++;
	}
	return (i);
}
