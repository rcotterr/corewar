/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 18:55:18 by tdontos-          #+#    #+#             */
/*   Updated: 2019/09/25 18:49:01 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

t_cmd	*create_cmd(t_type *file, t_header *head)
{
	int		i;
	t_cmd	*cmd;

	cmd = new_cmd(NULL);
	i = -1;
	while (++i < file[0].count)
	{
		if (file[i].type == LABEL || file[i].type == INS)
		{
			cmd->lbl = file[i].type == LABEL ? ft_strsub(file[i].str, 0,
				ft_strlen(file[i].str) - 1) : NULL;
			i += save_cmd(cmd, &file[i], file[0].count);
			cmd->next = new_cmd(cmd);
			cmd = cmd->next;
		}
	}
	del_cmd(cmd, 1);
	head->prog_size = roll_back(&cmd);
	return (cmd);
}

int		save_cmd(t_cmd *cmd, t_type *file, int max)
{
	int		i;
	int		reg;

	i = repeat_lbl(cmd, file, max - 1);
	if (i == -1)
		return (0);
	reg = output_oper(file[i].str);
	if (reg == -1)
		return (0);
	if (g_op_tab[reg].nb_arg > 1 || ft_strcmp(g_op_tab[reg].name, "aff") == 0)
		cmd->size += 1;
	while (file[i].type != NL)
	{
		if (file[i].type == INS)
			cmd->size += 1;
		else if (file[i].type == REG)
			cmd->size += 1;
		else if (file[i].type == DIR)
			cmd->size += g_op_tab[reg].label == 0 ? 4 : 2;
		else if (file[i].type == INDIR)
			cmd->size += 2;
		i++;
	}
	return (i);
}

t_cmd	*new_cmd(t_cmd *last)
{
	t_cmd	*cmd;

	cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd));
	cmd->prev = last;
	cmd->id = last == NULL ? 0 : last->id + 1;
	cmd->lbl = NULL;
	cmd->size = 0;
	return (cmd);
}

void	del_cmd(t_cmd *cmd, int count)
{
	int		all;

	all = count < 0 ? 1 : 0;
	if (count < 0)
	{
		while (cmd->next != NULL)
			cmd = cmd->next;
		count = cmd->id;
	}
	while (count > 0 && cmd->prev != NULL)
	{
		if (cmd->lbl != NULL)
			ft_strdel(&cmd->lbl);
		free(cmd->next);
		cmd->next = NULL;
		cmd = cmd->prev;
		count--;
	}
	if (all == 1)
	{
		free(cmd->next);
		free(cmd);
		if (cmd->lbl != NULL)
			free(cmd->lbl);
	}
}

int		roll_back(t_cmd **cmd)
{
	int		size;

	size = 0;
	while ((*cmd)->prev != NULL)
	{
		size += (*cmd)->size;
		*cmd = (*cmd)->prev;
	}
	size += (*cmd)->size;
	return (size);
}
