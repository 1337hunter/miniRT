/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 22:51:05 by gbright           #+#    #+#             */
/*   Updated: 2020/06/18 11:16:32 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_size(char *s)
{
	int	c;

	c = 0;
	if (s == 0)
		return (0);
	while (s[c] != 0)
		c++;
	return (c);
}

static int	my_get_line(int fd, char **line, char **fds, int i)
{
	int		j;
	char	*temp;

	if (!(*line = (char*)malloc(sizeof(char) * (i + 1))))
		return (-1);
	i = 0;
	while (fds[fd][i] != '\n' && fds[fd][i] && fds[fd])
	{
		(*line)[i] = fds[fd][i];
		i++;
	}
	(*line)[i] = 0;
	j = ft_size(fds[fd]);
	if (fds[fd][i] == '\n')
		i++;
	if (!(temp = (char*)malloc(sizeof(char) * (j - i + 1))))
		return (-1);
	temp[j - i] = 0;
	j = 0;
	while (fds[fd][i])
		temp[j++] = fds[fd][i++];
	free(fds[fd]);
	fds[fd] = temp;
	return (1);
}

static	int	my_find_line(int fd, char **line, char **fds, char *buf)
{
	int		i;

	i = 0;
	if (ft_size(fds[fd]) == 0)
	{
		if (!(*line = (char*)malloc(sizeof(char))))
			return (-1);
		**line = 0;
		free(fds[fd]);
		fds[fd] = 0;
		return (0);
	}
	while (fds[fd][i] && fds[fd][i] != '\n')
		i++;
	if (fds[fd][i] == '\n')
		return (my_get_line(fd, line, fds, i));
	else if (fds[fd][i] == 0 && ft_size(buf) == 0 && i != 0)
	{
		*line = fds[fd];
		fds[fd] = 0;
		return (0);
	}
	return (2);
}

static int	my_record(int fd, char **line, char *buf, char **fds)
{
	int		f_l;
	int		b_l;
	char	*temp;

	f_l = ft_size(fds[fd]);
	b_l = ft_size(buf);
	if (!(temp = (char*)malloc(sizeof(char) * (b_l + f_l + 1))))
		return (-1);
	temp[b_l + f_l] = 0;
	while (--b_l >= 0)
		temp[b_l + f_l] = buf[b_l];
	while (--f_l >= 0)
		temp[f_l] = fds[fd][f_l];
	free(fds[fd]);
	fds[fd] = temp;
	return (my_find_line(fd, line, fds, buf));
}

int			get_next_line(int fd, char **line)
{
	static char	*fds[1000];
	char		buf[BUFFER_SIZE + 1];
	int			red;
	int			flag;

	if (fd < 0 || (read(fd, buf, 0) < 0) || line == 0)
		return (-1);
	while ((red = read(fd, buf, BUFFER_SIZE)))
	{
		buf[red] = 0;
		flag = my_record(fd, line, buf, fds);
		if (flag == 0)
			return (0);
		else if (flag == 1)
			return (1);
		else if (flag == -1)
			return (-1);
	}
	buf[red] = 0;
	return (my_find_line(fd, line, fds, buf));
}
