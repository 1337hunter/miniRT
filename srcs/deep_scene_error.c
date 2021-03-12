/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deep_scene_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:21:30 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:34:16 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

char		*check_vector(char *v)
{
	v = skip_space(v);
	if (*v == 0)
		return (0);
	if ((*v < '0' || *v > '9') && *v != '-' && *v != '+')
		return (0);
	v = ft_strchr(v, ',');
	if (!v)
		return (0);
	v++;
	if ((*v < '0' || *v > '9') && *v != '-' && *v != '+')
		return (0);
	v = ft_strchr(v, ',');
	if (!v)
		return (0);
	v++;
	if ((*v < '0' || *v > '9') && *v != '-' && *v != '+')
		return (0);
	v = skip_float(v);
	return (v);
}

static void	my_cam_error(char *c)
{
	if (!(c = check_vector(c)))
		exit_status("Error\nCamera error\n");
	if (*c != ' ')
		exit_status("Error\nCamera error\n");
	c = skip_space(c);
	if (!(c = check_vector(c)))
		exit_status("Error\nCamera error\n");
	c = skip_space(c);
	if ((*c < '0' || *c > '9') && *c != '-' && *c != '+')
		exit_status("Error\nCamera FOV is tutu\n");
}

static void	my_light_error(char *l)
{
	if (*l != ' ')
		exit_status("Error\nLight or sphere error\n");
	if (!(l = check_vector(l)))
		exit_status("Error\nLight error\n");
	l = skip_space(l);
	if ((*l < '0' || *l > '9') && *l != '-' && *l != '+')
		exit_status("Error\nLight or sphere error\n");
	l = skip_float(l);
	if (!(l = check_vector(l)))
		exit_status("Error\nLight or sphere error\n");
}

static void	my_pl_error(char *pl)
{
	if (*pl != ' ')
		exit_status("Error\nPlane error\n");
	if (!(pl = check_vector(pl)))
		exit_status("Error\nPlane error\n");
	if (!(pl = check_vector(pl)))
		exit_status("Error\nPlane error\n");
	if (!(pl = check_vector(pl)))
		exit_status("Error\nPlane error\n");
}

void		deep_scene_error(char **sn)
{
	while (*sn)
	{
		if (ft_strncmp(*sn, "c ", 2) == 0)
			my_cam_error(*sn + 1);
		if (ft_strncmp(*sn, "l ", 2) == 0)
			my_light_error(*sn + 1);
		if (ft_strncmp(*sn, "sp", 2) == 0)
			my_light_error(*sn + 2);
		if (ft_strncmp(*sn, "pl", 2) == 0)
			my_pl_error(*sn + 2);
		if (ft_strncmp(*sn, "sq", 2) == 0)
			error_sq(*sn + 2);
		if (ft_strncmp(*sn, "cy", 2) == 0)
			error_cy(*sn + 2);
		if (ft_strncmp(*sn, "tr", 2) == 0)
			error_tr(*sn + 2);
		sn++;
	}
}
