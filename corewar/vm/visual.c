/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:18:58 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/24 18:26:24 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			deal_key(int key, void *vm)
{
	if ((int)key == 53)
	{
		mlx_destroy_window(((t_vm *)vm)->vis->mlx_ptr,
			((t_vm *)vm)->vis->win_ptr);
		exit(0);
	}
	if ((int)key == 49)
	{
		step((t_vm *)vm);
		change_window((t_vm *)vm);
	}
	return (0);
}

void		change_window(t_vm *vm)
{
	mlx_clear_window(vm->vis->mlx_ptr, vm->vis->win_ptr);
	draw_arena(*vm, *(vm->vis));
	draw_frames(*vm, *(vm->vis));
	draw_carrigies(*vm, *(vm->vis));
}

t_visual	visual(t_vm vm)
{
	t_visual	vis;

	if (!(vis.mlx_ptr = mlx_init()))
		exit(0);
	if (!(vis.win_ptr = mlx_new_window(vis.mlx_ptr, 2100, 1070, "Corewar")))
		exit(0);
	vis.arena_colour = ft_memalloc(sizeof(t_byte) * MEM_SIZE);
	vis.arena_colour = fill_arena_colour(vm, vis.arena_colour);
	vis.colour = make_colour();
	vm.vis = &vis;
	col_carrigies(&vm);
	draw_arena(vm, vis);
	draw_frames(vm, vis);
	draw_carrigies(vm, vis);
	if (!vm.flags.v_debug)
		mlx_loop_hook(vis.mlx_ptr, step, &vm);
	mlx_hook(vis.win_ptr, 2, 1, deal_key, &vm);
	mlx_loop(vis.mlx_ptr);
	return (vis);
}
