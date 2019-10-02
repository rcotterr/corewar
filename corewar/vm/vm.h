/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcotter- <rcotter-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 01:45:39 by jdesmond          #+#    #+#             */
/*   Updated: 2019/09/25 12:31:23 by rcotter-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
# define COREWAR_VM_H

# include "op.h"
# include "mlx.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>
# include "carriage.h"

# define FLAG_NUM "n"
# define FLAG_DUMP "dump"
# define FLAG_VIS "v"
# define FLAG_DEBUG "debug"
# define FLAG_LIVE "live"

# define FRAME 20
# define COLUMN_DIF 26
# define ROW_DIF 16

# define GREY 0x808080
# define PINK 0xff6781
# define YELLOW 0xFFFACD
# define GREEN 0x3CB371
# define BLUE 0x87CEFA
# define WHITE 0xFFFFFF

union					u_byte
{
	int					ints;
	char				chars[4];
};

typedef unsigned char	t_byte;

typedef	struct			s_champ
{
	t_byte				*exec_code;
	int					size;
	char				*name;
	char				*comment;
	int					player_number;
}						t_champ;

typedef struct			s_champ_info
{
	char				*info;
	int					len;
}						t_champ_info;

typedef struct			s_car_list
{
	t_carriage			*car;
	struct s_car_list	*next;
}						t_car_list;

typedef struct			s_flag
{
	int					n;
	int					dump;
	int					dump_num;
	int					v;
	int					v_debug;
	int					live;
}						t_flag;

typedef struct			s_visual
{
	void				*mlx_ptr;
	void				*win_ptr;
	unsigned char		*arena_colour;
	int					*colour;
}						t_visual;

typedef struct			s_vm
{
	t_car_list			*car_list;
	t_byte				*arena;
	t_champ				**champs;
	t_flag				flags;
	t_champ				*last_champ_alive;
	int					cycle_number;
	int					num_of_players;
	int					cycles_to_die;
	int					turns_since_last_check;
	int					live_since_last_check;
	int					checks_since_last_change;
	t_visual			*vis;
}						t_vm;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_draw
{
	float				err;
	float				derr;
	int					step_x;
	int					step_y;
	int					x;
	int					y;
	int					delta;
	int					error;
}						t_draw;

t_champ_info			get_champ_info(int fd);
t_champ					*create_champ(t_champ_info champ_info, char *arg);
void					print_champ(t_champ *champ);
void					validate_champ(t_champ *champ, t_champ_info champ_info);
t_champ_info			get_champ_info(int fd);
char					*get_champ_name(char *champ_info);
char					*get_champ_comment(char *champ_info);
unsigned char			*get_champ_exec_code(t_champ_info champ_info);
int						get_champ_size(char *champ_info);
unsigned int			reverse(unsigned int x, int size);
void					validate_champ(t_champ *champ, t_champ_info champ_info);
int						check_null(char *champ_info);
int						check_header(char *champ_info);
int						crash(char *s);
t_vm					create_vm(void);
t_carriage				*create_carriage(int player_num);
t_carriage				*fork_carriage(t_carriage *car, int position);
t_visual				visual(t_vm vm);
char					*ft_hex(unsigned long long int o, char format);
void					game_cycle(t_vm *vm);
void					print_arena_32(unsigned char *arena);
void					write_to_arena(t_vm *vm, t_byte *to_write,
										int position, int length);
void					change_window(t_vm *vm);
int						bytes_to_int(t_byte *bytes, int byte_num);
void					process_flag_n(t_vm *vm, t_champ *champ);
int						is_flag(char *arg);
void					process_flags(t_vm *vm, char **argv);
void					print_winner(t_vm vm);
void					print_players(t_vm vm);
void					print_arena_32(unsigned char *arena);
void					make_num_players(t_vm *vm);
void					process_arg(t_vm *vm, char **argv);
void					init_arena(t_vm *vm);
void					do_opp(t_vm *vm, t_carriage *car);
void					process_flag_dump(t_vm *vm);
void					print_vm_champs(t_vm vm);
t_carriage				*fork_carriage(t_carriage *car, int position);
void					print_cars(t_car_list *car);
int						get_int_arg(t_byte *part_arena, int size);
t_byte					*int_to_bytes(int ints, t_byte *where, int ind);
int						arena_ind(int ind);
int						step(t_vm *vm);
void					change_window(t_vm *vm);
void					change_arena_col(unsigned char *arena_col,
						int adress, int col);
void					vis_winner(t_vm *vm);
int						check_registr(t_carriage *car, int reg);
unsigned char			*fill_arena_colour(t_vm vm, unsigned char *arena_col);
int						*make_colour(void);
void					col_carrigies(t_vm *vm);
void					draw_line(t_point p1, t_point p2, t_visual vis,
						int colour);
void					draw_circle(t_visual vis, t_point p, int radius,
						int col);
void					draw_arena(t_vm vm, t_visual vis);
void					draw_players(t_vm vm, t_visual vis);
void					draw_keys(t_visual vis);
void					draw_vm_info(t_vm vm, t_visual vis);
void					draw_frames(t_vm vm, t_visual vis);
void					draw_carrigies(t_vm vm, t_visual vis);
void					manage_dying(t_vm *vm);
void					handle_waiting(t_vm *vm, t_car_list *car);
int						need_check(t_vm *vm);
void					modify_cycles_to_die(t_vm *vm);
int						is_number(char *arg);
void					change_carry(t_carriage *car, int result);
void					write_to_reg(t_vm *vm, t_carriage *car, int *args,
						int adress);

#endif
