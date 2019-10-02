/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:12:08 by tdontos-          #+#    #+#             */
/*   Updated: 2019/09/14 14:24:35 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*ft_hex(unsigned long long int o, char format)
{
	int		module[15];
	int		i;
	char	*hex;
	char	reg;
	int		j;

	j = 0;
	i = 0;
	if (o == 0)
		return (ft_strdup("0"));
	reg = format == 'X' ? 'A' : 'a';
	while (o != 0)
	{
		module[i++] = o % 16;
		o /= 16;
	}
	hex = ft_strnew(i + 1);
	if (hex == NULL)
		return (NULL);
	hex[i] = '\0';
	while (i > 0)
		hex[j++] = module[--i] > 9 ? module[i] - 10 + reg : module[i] + 48;
	return (hex);
}

int		get_int_arg(t_byte *part_arena, int size)
{
	int				i;
	int				nbr;
	union u_byte	byte;

	byte.ints = 0;
	i = 0;
	while (i < size)
	{
		byte.chars[4 - size + i] = part_arena[arena_ind(i)];
		i++;
	}
	nbr = reverse(byte.ints, 4);
	if (size == 2)
		nbr = (short int)nbr;
	return (nbr);
}
