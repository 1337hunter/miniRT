/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_deal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:21:11 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 14:03:47 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

void	set_color(short *out, short r, short g, short b)
{
	out[0] = r;
	out[1] = g;
	out[2] = b;
}

int		get_color(short *rgb)
{
	int	res;

	res = rgb[0];
	res = (res << 8) + rgb[1];
	res = (res << 8) + rgb[2];
	return (res);
}

void	color_check(t_scene *sn)
{
	int	i;

	i = -1;
	while (++i < 3)
		if (sn->color[i] > 255 || sn->color[i] < 0)
			sn->color[i] = 255;
	if (sn->sepia)
		sepia(sn->color);
}

void	color_intensity(short *color, double *ki)
{
	int	i;

	i = -1;
	while (++i < 3)
		if (ki[i] < 0 || ki[i] > 1)
			ki[i] = 1;
	i = -1;
	while (++i < 3)
		color[i] = color[i] * ki[i];
}

void	sepia(short *rgb)
{
	short	t[3];

	t[0] = rgb[0] * 0.393 + rgb[1] * 0.769 + rgb[2] * 0.189;
	t[1] = rgb[0] * 0.349 + rgb[1] * 0.686 + rgb[2] * 0.168;
	t[2] = rgb[0] * 0.272 + rgb[1] * 0.534 + rgb[2] * 0.131;
	rgb[0] = t[0];
	rgb[1] = t[1];
	rgb[2] = t[2];
	rgb[0] = (rgb[0] > 255 || rgb[0] < 0 ? 255 : rgb[0]);
	rgb[1] = (rgb[1] > 255 || rgb[1] < 0 ? 255 : rgb[1]);
	rgb[2] = (rgb[2] > 255 || rgb[2] < 0 ? 255 : rgb[2]);
}
