/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis-asm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:39:00 by tdontos-          #+#    #+#             */
/*   Updated: 2019/09/25 16:11:02 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/disasm.h"

int			g_fd_new = -1;
int			g_fd_read = -1;

int		main(int argc, char **argv)
{
	int		flag;

	flag = 0;
	if (argc == 3 && ft_strcmp(argv[2], "-h") == 0)
		flag = 1;
	else if (argc != 2)
		return (usage(argv[0]));
	g_fd_new = init_file_s(argv[1], flag);
	g_fd_read = open(argv[1], O_RDONLY);
	if (g_fd_read <= 0)
		return (usage(argv[0]));
	section();
	close(g_fd_read);
	close(g_fd_new);
	return (0);
}

int		init_file_s(char *name, int flag)
{
	int		fd;
	char	*type;
	char	*fname;
	char	*nametype;

	if (flag == 1)
		clear_dir(&name);
	type = ft_strchr(name, '.');
	if (type == NULL || ft_strstr(type, "cor") == NULL || ft_strlen(type) != 4)
		exit(1);
	type = "s";
	fname = ft_strsub(name, 0, ft_strlen(name) - 3);
	nametype = ft_strjoin(fname, type);
	free(fname);
	fd = open(nametype, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	ft_putstr("Writing output program to ");
	ft_putendl(nametype);
	free(nametype);
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
	while (path[i] > 0)
	{
		--i;
		ft_strdel(&path[i]);
	}
	free(path);
}

int		usage(char *name)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(" <sourcefile.s>\n", 2);
	return (0);
}
