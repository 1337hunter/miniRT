/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:22:25 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:28:32 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"

static int	my_count_lines(char **av)
{
	int		c;
	int		fd;
	int		red;
	char	buf;

	if ((fd = open(av[1], O_RDWR)) == -1)
		perr_handle();
	c = 1;
	red = 1;
	buf = 0;
	while (red)
	{
		red = read(fd, &buf, 1);
		if (buf == '\n')
			c++;
	}
	close(fd);
	return (c);
}

t_scene		*get_scene(char **av)
{
	char	**out;
	int		fd;
	int		size;
	t_scene	*scene;
	int		error;

	size = my_count_lines(av);
	if ((fd = open(av[1], O_RDWR)) == -1)
		perr_handle();
	if (!(out = (char**)malloc(sizeof(char*) * (size + 1))))
		perr_handle();
	size = 0;
	while ((error = get_next_line(fd, &out[size++])) > 0)
		;
	if (error == -1)
		exit_status("Error\nError while reading scene file\n");
	out[size] = 0;
	err_scene(out);
	scene = parse_scene(out);
	size = 0;
	while (out[size])
		free(out[size++]);
	free(out);
	return (scene);
}
