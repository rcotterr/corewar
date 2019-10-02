/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 23:37:01 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/14 14:25:20 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opp1.h"
#include "opp2.h"
#include "opp3.h"
#include "opp4.h"
#include "op.h"
#include "fun_tub.h"

t_opp_info	g_fun_tab[OPP_TAB_LENGTH] =
{
	{0, opp_live},
	{1, opp_ld},
	{2, opp_st},
	{3, opp_add},
	{4, opp_sub},
	{5, opp_and},
	{6, opp_or},
	{7, opp_xor},
	{8, opp_zjmp},
	{9, opp_ldi},
	{10, opp_sti},
	{11, opp_fork},
	{12, opp_lld},
	{13, opp_lldi},
	{14, opp_lfork},
	{15, opp_aff}
};
