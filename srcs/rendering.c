/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:27:07 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 13:56:39 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"

static void	my_render_tr(t_scene *sn)
{
	int	i;

	i = -1;
	while (++i < sn->shapes.ntr)
	{
		sn->trn = i;
		vector_sub_f(sn->c[sn->cu].xyz, sn->shapes.tr[i].b,
				sn->shapes.tr[i].op, 3);
		intersect_tr(sn);
	}
	i = -1;
	while (++i < sn->shapes.ncy)
	{
		sn->cyn = i;
		vector_sub_f(sn->c[sn->cu].xyz, sn->shapes.cy[i].xyz,
				sn->shapes.cy[i].oc, 3);
		intersect_cy(sn);
	}
}

static void	my_render_sq(t_scene *sn)
{
	int		i;

	i = -1;
	while (++i < sn->shapes.nsq)
	{
		sn->sqn = i;
		vector_sub_f(sn->c[sn->cu].xyz, sn->shapes.sq[i].xyz,
				sn->shapes.sq[i].op, 3);
		intersect_sq(sn);
	}
	my_render_tr(sn);
}

static void	my_render(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->shapes.nsp)
	{
		scene->spn = i;
		vector_sub_f(scene->c[scene->cu].xyz, ((scene->shapes.sp)[i]).xyz,
				((scene->shapes.sp)[i]).oc, 3);
		intersect_sp(scene);
	}
	i = -1;
	while (++i < scene->shapes.npl)
	{
		scene->pln = i;
		vector_sub_f(scene->c[scene->cu].xyz, ((scene->shapes.pl)[i]).xyz,
				(scene->shapes.pl)[i].po, 3);
		intersect_pl(scene);
	}
	my_render_sq(scene);
}

void		rendering(t_scene *scene, t_img *img, t_mlx *mlx)
{
	int		x;
	int		y;

	y = (scene->h / 2) + 1;
	while (--y > -(scene->h / 2))
	{
		x = -(scene->w / 2) - 1;
		while (++x < scene->w / 2)
		{
			scene->closest = 1.0 / 0.0;
			set_color(scene->color, 0, 0, 0);
			viewport_xyz(scene, x, y);
			my_render(scene);
			color_intensity(scene->color, scene->ki);
			color_check(scene);
			((int*)(img->data))[(scene->h / 2 - y) * scene->w +
				(scene->w / 2 + x)] = get_color(scene->color);
		}
	}
	if (scene->save)
		save_bmp("saved.bmp", (int*)img->data, scene->w, scene->h);
	else
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img, 0, 0);
}
