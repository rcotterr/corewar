/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 15:19:40 by tdontos-          #+#    #+#             */
/*   Updated: 2019/09/25 19:06:22 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int			g_fd_new = -1;
int			g_fd_read = -1;

int		main(int argc, char **argv)
{
	t_type		*file;
	t_header	*head;
	t_cmd		*cmd;
	char		*nametype;
	int			flag;

	nametype = NULL;
	flag = 0;
	if (argc == 3)
		flag = save_flag(argv);
	else if (argc != 2)
		return (usage(argv[0]));
	if ((file = read_file(argv[1])) == NULL)
		return (1);
	head = (t_header*)ft_memalloc(sizeof(t_header));
	g_fd_new = init_file(argv[1], flag, argv[0], &nametype);
	head->magic = COREWAR_EXEC_MAGIC;
	print_magic();
	cmd = create_cmd(file, head);
	print_top(head, file);
	check_file(file, cmd);
	del_cmd(cmd, -1);
	end_programm(&nametype, &file, &head, file[0].count);
	return (0);
}

int		init_file(char *name, int flag, char *prj, char **nametype)
{
	int		fd;
	char	*type;
	char	*fname;

	if (flag == 1)
		clear_dir(&name);
	type = &name[ft_strlen(name) - 2];
	if (type == NULL || type[0] != '.' || type[1] != 's')
	{
		usage(prj);
		exit(1);
	}
	type = "cor";
	fname = ft_strsub(name, 0, ft_strlen(name) - 1);
	*nametype = ft_strjoin(fname, type);
	free(fname);
	if (flag == 1)
		free(name);
	fd = open(*nametype, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	return (fd);
}

void	clear_dir(char **name)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_strsplit(*name, '/');
	while (path[i] != NULL)
		i++;
	*name = ft_strdup(path[i - 1]);
	while (i >= 0)
	{
		ft_strdel(&path[i]);
		--i;
	}
	free(path);
}

int		save_flag(char **flag)
{
	int		i;

	i = 0;
	while (++i <= 2)
	{
		if (ft_strcmp(flag[i], "-h") == 0)
			return (1);
	}
	usage(flag[0]);
	exit(1);
}

void	print_top(t_header *head, t_type *file)
{
	int		i;

	i = -1;
	while (++i != file[0].count)
	{
		if (ft_strcmp(file[i].str, NAME_CMD_STRING) == 0)
		{
			check_line(head, &file[i]);
			break ;
		}
	}
	i = -1;
	while (++i != file[0].count)
	{
		if (ft_strcmp(file[i].str, COMMENT_CMD_STRING) == 0)
		{
			check_line(head, &file[i]);
			break ;
		}
	}
}
