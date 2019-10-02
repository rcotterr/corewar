/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis-asm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:39:42 by tdontos-          #+#    #+#             */
/*   Updated: 2019/09/02 19:39:43 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H
# include "libft.h"
# include "op.h"
# include <fcntl.h>

extern int	g_fd_new;
extern int	g_fd_read;

typedef union		u_byte
{
	unsigned int	ints;
	unsigned char	chars[4];
}					t_byte;

int					init_file_s(char *name, int file);
void				clear_dir(char **name);

void				skip_bytes(int count);
int					check_magic(void);
unsigned int		reverse(unsigned int x, int cnt);
void				valid_error(int code);

void				section(void);
void				input_code(int max_size);
int					read_cmd(void);
void				read_args(int count, int index, int *args);
int					digit_arg(int size);

int					*count_args(int index);
int					usage(char *name);

#endif
