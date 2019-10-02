/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 15:35:14 by tdontos-          #+#    #+#             */
/*   Updated: 2019/09/15 15:59:04 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"
# include <fcntl.h>

# define NL			0
# define STR		1
# define INS		2
# define LABEL		3
# define REG		4
# define SEP		5
# define DIR_L		6
# define DIR		7
# define INDIR		8
# define CMD		9

extern int	g_fd_new;
extern int	g_fd_read;

typedef struct		s_type
{
	int				count;
	char			type;
	char			*str;
	int				i;
	int				j;
}					t_type;

typedef struct		s_cmd
{
	int				id;
	char			*lbl;
	int				size;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef union		u_byte
{
	unsigned int	ints;
	unsigned char	chars[4];
}					t_byte;

int					inttolong(char flag, long ij);
void				direr(char *str);
char				*str3(int i);
int					lexical_er(int x, int i);
int					usage(char *name);
int					open_str(void);
int					synerr(t_type type);
int					inval_par(int ind, char *ins, char type, t_type types);
int					inval_ins(t_type type);
int					double_lab(t_type *types, int i, int j);
int					no_dirlabel(t_type types);
int					null_as(t_type types);

int					add_c_str(t_type **types, char c, long *mod, char **str);
int					ch_dir(t_type **types, int i, int *j, char **list);
int					ch_indir(t_type **types, int i, int *j, char **list);
int					ch_label(t_type **types, int i, int *j, char **list);
int					ch_reg(t_type **types, int i, int *j, char **list);
int					ch_ins(t_type **types, int i, int *j, char **list);
int					ch_com(t_type **types, int i, int *j, char **list);
int					end_str(long ij, char **list, long *mod, char **str);
int					nl(long mod, t_type **types, int i, int j);
int					ch_sep(long mod, long ij, t_type **types, char **list);
t_type				*ch_open_str(long mod, char **str, t_type **ty);
int					ch_all(t_type **ty, int i, int *j, char **l);
int					cadd(long mod, char **str);
t_type				*del_type(t_type **ty);
t_type				*set_arr(int *i, long *mod);

char				*addcstr(char *str, char c);
char				*isdir(char *str, int x);
long				itol(int i, int j);
char				*isindir(char *str, int x);
char				*isreg(char *str, int x);
char				*islabel(char *str, int x);
char				*isins(char *str, int x);
char				*com(char *str, int x);
int					islchar(char c);
int					isvalidend(char c);
char				*delcomment(char *str);
long				itoln(int i, int j);
t_type				*settype(char **l, int i, int j, long mod);
int					valid_id_arg(int ins, int ind, t_type types);
char				get_code(t_type type);
int					label_dir(char *s2, char *s1);
int					double_label(t_type *t);

int					lexical_er(int x, int i);

void				check_file(t_type *file, t_cmd *cmd);
int					check_line(t_header *head, t_type *file);
void				pars_line(char *line, int size, t_type *file);
int					pars_lbl(t_type *file, t_cmd *cmd, int max, int pos);
int					output_oper(char *line);
int					pars_arg(t_type *file, int index, t_cmd *cmd);

int					read_arg(char *arg, int index);
char				arg_sums(char bits, int type);
int					write_arg(t_type *file, int tdir, t_cmd *cmd);

int					init_file(char *name, int flag, char *prj, char **nametype);

int					make_bin(char *line, int size, int nll);
void				valid_error(int code, int size);
void				print_magic(void);
unsigned int		reverse(unsigned int x, int cnt);

void				del_cmd(t_cmd *cmd, int count);
t_cmd				*create_cmd(t_type *file, t_header *head);
t_cmd				*new_cmd(t_cmd *last);
int					save_cmd(t_cmd *cmd, t_type *file, int max);
int					roll_back(t_cmd **cmd);
int					search_lbl_prev(char *str, t_cmd *cmd);
int					search_lbl_next(char *str, t_cmd *cmd);

t_type				*valid(char **list);

int					synerr(t_type file);
char				**addlist(char **list, char *str);
char				**dellist(char **list);
char				*delcomment(char *str);
t_type				*read_file(char *name);

t_type				*addtype(t_type *types, char *str, char type, long l);
t_type				*cpytype(t_type *be, t_type *to, int x);
t_type				*deltype(t_type *types, int strs);
t_type				*setmemtype(t_type *types, int i);

char				*isins(char *str, int x);
char				*isindir(char *str, int x);
int					open_str(void);
int					usage(char *str);

int					inval_ins(t_type file);
int					inval_par(int ind, char *ins, char type, t_type types);
void				clear_dir(char **name);

int					repeat_lbl(t_cmd *cmd, t_type *file, int max);
int					save_flag(char **flag);

void				print_top(t_header *head, t_type *file);
void				end_programm(char **nametype, t_type **file,
					t_header **head, int count);
t_byte				type_date(t_byte args, int *size, t_cmd *cmd, t_type file);
int					check_nl(char *name, int fd);

#endif
