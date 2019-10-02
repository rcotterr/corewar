/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 00:26:58 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/11 15:19:25 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPP1_H
# define OPP1_H
# include "carriage.h"
# include "vm.h"

void	opp_live(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_ld(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_st(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_add(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_sub(t_vm *vm, t_carriage *car, int *args, char *argtypes);

#endif
