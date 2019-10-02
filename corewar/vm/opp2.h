/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdesmond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 00:40:00 by jdesmond          #+#    #+#             */
/*   Updated: 2019/08/30 00:40:04 by jdesmond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPP2_H
# define OPP2_H
# include "carriage.h"
# include "vm.h"

void	opp_and(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_or(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_xor(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_zjmp(t_vm *vm, t_carriage *car, int *args, char *argtypes);
void	opp_ldi(t_vm *vm, t_carriage *car, int *args, char *argtypes);

#endif
