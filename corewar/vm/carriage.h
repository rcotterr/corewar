/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 00:15:32 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/23 17:00:52 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CARRIAGE_H
# define CARRIAGE_H

# include "op.h"

typedef unsigned char	t_byte;

typedef struct			s_carriage
{
	int					id;
	t_byte				regs[REG_NUMBER][REG_SIZE];
	t_byte				carry;
	int					position;
	int					step;
	int					live;
	t_byte				opcode;
	int					waiting;
	int					colour;
}						t_carriage;

t_carriage				*create_carriage(int player_num);
t_carriage				*copy_carriage(t_carriage *car, int position);

#endif
