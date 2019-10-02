/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 12:39:07 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/14 13:57:19 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*make_hex_arena(t_vm vm, int i, char *s)
{
	char	*tmp;

	s = ft_hex(vm.arena[i], 1);
	if (ft_strlen(s) == 1)
	{
		tmp = s;
		s = ft_strjoin("0", s);
		free(tmp);
	}
	return (s);
}

void	draw_arena(t_vm vm, t_visual vis)
{
	int		i;
	int		row;
	int		column;
	char	*s;

	i = 0;
	row = 0;
	column = 0;
	while (i < MEM_SIZE)
	{
		s = make_hex_arena(vm, i, s);
		mlx_string_put(vis.mlx_ptr, vis.win_ptr, FRAME + column, FRAME + row,
			vis.colour[vis.arena_colour[i]], s);
		free(s);
		column += COLUMN_DIF;
		i++;
		if (!(i % 64))
		{
			row += ROW_DIF;
			column = 0;
		}
	}
}

void	draw_players(t_vm vm, t_visual vis)
{
	int		i;
	int		x;
	int		y;
	t_champ	*champ;
	char	*s;

	i = 0;
	x = 1720;
	y = 200;
	while (i < vm.num_of_players)
	{
		champ = (vm.champs)[i];
		mlx_string_put(vis.mlx_ptr, vis.win_ptr, x, y,
			vis.colour[champ->player_number], "Player ");
		x += 80;
		s = ft_itoa(champ->player_number);
		mlx_string_put(vis.mlx_ptr, vis.win_ptr, x, y,
			vis.colour[champ->player_number], s);
		free(s);
		x = 1720;
		y += 20;
		mlx_string_put(vis.mlx_ptr, vis.win_ptr, x, y, WHITE, champ->name);
		y += 100;
		i++;
	}
}

void	draw_keys(t_visual vis)
{
	t_point		p1;
	t_point		p2;

	p1.x = 1700;
	p1.y = 0;
	p2.x = 1700;
	p2.y = 1070;
	draw_line(p1, p2, vis, GREY);
	mlx_string_put(vis.mlx_ptr, vis.win_ptr, 1720, 1010, WHITE,
		"Press 'space' to start in debug");
	mlx_string_put(vis.mlx_ptr, vis.win_ptr, 1720, 1030, WHITE,
		"Press 'esc' to quit the programm");
}

void	draw_vm_info(t_vm vm, t_visual vis)
{
	int		x;
	int		y;
	char	*s;

	x = 1720;
	y = 30;
	mlx_string_put(vis.mlx_ptr, vis.win_ptr, x, y, WHITE,
		"Cycle_number:");
	x += 150;
	s = ft_itoa(vm.cycle_number);
	mlx_string_put(vis.mlx_ptr, vis.win_ptr, x, y, WHITE, s);
	free(s);
}
