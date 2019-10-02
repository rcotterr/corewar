/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_tub.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:45:04 by rcotter-          #+#    #+#             */
/*   Updated: 2019/09/09 16:45:27 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUN_TUB_H
# define FUN_TUB_H

struct s_vm;
typedef struct		s_opp_info
{
	int		opp_tab_index;
	void	(*fun)(struct s_vm*, t_carriage*, int*, t_arg_type *);
}					t_opp_info;
extern t_opp_info	g_fun_tab[OPP_TAB_LENGTH];

#endif
