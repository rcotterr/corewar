/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdesmond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 00:40:36 by jdesmond          #+#    #+#             */
/*   Updated: 2019/08/30 00:40:42 by jdesmond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPP3_H
# define OPP3_H
# include "carriage.h"
# include "vm.h"

void	opp_sti(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_fork(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_lld(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_lldi(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_lfork(t_vm *vm, t_carriage *car, int *args, char *argtypes);

#endif
