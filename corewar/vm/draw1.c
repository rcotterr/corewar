/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 12:36:47 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/14 13:56:55 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_circle(t_visual vis, t_point p, int radius, int col)
{
	t_draw	dr;

	dr.x = 0;
	dr.y = radius;
	dr.error = 0;
	dr.delta = 1 - 2 * radius;
	while (dr.y >= 0)
	{
		mlx_pixel_put(vis.mlx_ptr, vis.win_ptr, p.x + dr.x, p.y + dr.y, col);
		mlx_pixel_put(vis.mlx_ptr, vis.win_ptr, p.x + dr.x, p.y - dr.y, col);
		mlx_pixel_put(vis.mlx_ptr, vis.win_ptr, p.x - dr.x, p.y + dr.y, col);
		mlx_pixel_put(vis.mlx_ptr, vis.win_ptr, p.x - dr.x, p.y - dr.y, col);
		dr.error = 2 * (dr.delta + dr.y) - 1;
		if ((dr.delta < 0) && (dr.error <= 0))
		{
			dr.delta = dr.delta + 2 * ++dr.x + 1;
			continue ;
		}
		if ((dr.delta > 0) && (dr.error > 0))
		{
			dr.delta = dr.delta - 2 * --dr.y + 1;
			continue ;
		}
		dr.delta = dr.delta + 2 * (++dr.x - --dr.y);
	}
}

void	draw_line(t_point p1, t_point p2, t_visual vis, int colour)
{
	t_draw	draw;

	draw.step_x = (p2.x > p1.x) ? 1 : -1;
	draw.step_y = (p2.y > p1.y) ? 1 : -1;
	if (p1.x == p2.x)
	{
		while ((p1.y += draw.step_y) != p2.y + draw.step_y)
			mlx_pixel_put(vis.mlx_ptr, vis.win_ptr, p1.x, p1.y, colour);
		return ;
	}
	draw.err = 0.0;
	draw.derr = (float)(p2.y - p1.y) / (float)(p2.x - p1.x);
	draw.derr = (draw.derr > 0) ? draw.derr : -draw.derr;
	while ((p1.x += draw.step_x) != p2.x + draw.step_x)
	{
		mlx_pixel_put(vis.mlx_ptr, vis.win_ptr, p1.x, p1.y, colour);
		draw.err += draw.derr;
		while (draw.err >= 0.5)
		{
			p1.y += draw.step_y;
			draw.err -= 1.0;
			mlx_pixel_put(vis.mlx_ptr, vis.win_ptr, p1.x, p1.y, colour);
		}
	}
}

void	vis_winner(t_vm *vm)
{
	t_champ *champ;
	t_point p;

	champ = vm->last_champ_alive;
	mlx_clear_window(vm->vis->mlx_ptr, vm->vis->win_ptr);
	draw_frames(*vm, *(vm->vis));
	mlx_string_put(vm->vis->mlx_ptr, vm->vis->win_ptr, 800, 500,
		vm->vis->colour[champ->player_number], "THE WINNER IS PLAYER ");
	mlx_string_put(vm->vis->mlx_ptr, vm->vis->win_ptr, 1010, 500,
		vm->vis->colour[champ->player_number], ft_itoa(champ->player_number));
	mlx_string_put(vm->vis->mlx_ptr, vm->vis->win_ptr, 800, 540,
		vm->vis->colour[champ->player_number], champ->name);
	p.x = 50;
	p.y = 50;
	draw_circle(*(vm->vis), p, 250, vm->vis->colour[champ->player_number]);
	draw_circle(*(vm->vis), p, 240, vm->vis->colour[champ->player_number]);
	p.x = 1700;
	p.y = 1000;
	draw_circle(*(vm->vis), p, 240, vm->vis->colour[champ->player_number]);
	draw_circle(*(vm->vis), p, 250, vm->vis->colour[champ->player_number]);
}

void	draw_carrigies(t_vm vm, t_visual vis)
{
	t_car_list	*car;
	t_point		p1;
	t_point		p2;
	int			i;

	car = vm.car_list;
	i = vm.num_of_players - 1;
	p1.x = 20;
	p1.y = 20;
	while (car)
	{
		p1.x = FRAME + car->car->position % 64 * 26;
		p1.y = FRAME + car->car->position / 64 * 16 + 18;
		p2.x = p1.x + 20;
		p2.y = p1.y;
		draw_line(p1, p2, vis, vis.colour[car->car->colour]);
		p1.y -= 14;
		p2.y = p1.y;
		draw_line(p1, p2, vis, car->car->colour);
		car = car->next;
		i--;
	}
}

void	draw_frames(t_vm vm, t_visual vis)
{
	draw_keys(vis);
	draw_vm_info(vm, vis);
	draw_players(vm, vis);
}
