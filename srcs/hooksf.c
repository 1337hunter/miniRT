/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooksf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:25:19 by gbright           #+#    #+#             */
/*   Updated: 2020/07/04 13:49:24 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_press(int key, void *param)
{
	t_scene *sn;

	sn = (t_scene*)param;
	if (key == 124)
	{
		sn->cu = (sn->cu + 1) % sn->nc;
		rendering(sn, sn->img, sn->mlx);
	}
	if (key == 123)
	{
		if (sn->cu == 0)
			sn->cu = sn->nc - 1;
		else
			sn->cu = (sn->cu - 1) % sn->nc;
		rendering(sn, sn->img, sn->mlx);
	}
	if (key == 53)
		exit(0);
	return (0);
}

int	exit_program(void *param)
{
	param = 0;
	exit(0);
}
