/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_deal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 11:33:37 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 15:32:09 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	my_shadow_sp(t_scene *sn, double *dir, double *p, int i)
{
	double	a;
	double	b;
	double	c;
	double	discr;
	double	root[2];

	vector_sub_f(p, sn->shapes.sp[i].xyz, sn->shapes.sp[i].pc, 3);
	a = dot_f(dir, dir, 3);
	b = 2 * dot_f((sn->shapes.sp)[i].pc, dir, 3);
	c = dot_f((sn->shapes.sp)[i].pc, (sn->shapes.sp)[i].pc, 3) -
		sn->shapes.sp[i].d * sn->shapes.sp[i].d / 4;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	root[0] = (-b + sqrt(discr)) / (2 * a);
	root[1] = (-b - sqrt(discr)) / (2 * a);
	if ((root[0] > 0.001 && root[0] < 1))
		return (1);
	if ((root[1] > 0.001 && root[1] < 1))
		return (1);
	return (0);
}

static int	my_shadow_pl(t_scene *sn, double *dir, double *p, int i)
{
	double	root;

	vector_sub_f(p, sn->shapes.pl[i].xyz, sn->shapes.pl[i].cp, 3);
	root = -(dot_f(sn->shapes.pl[i].cp, sn->shapes.pl[i].n, 3) /
			dot_f(dir, sn->shapes.pl[i].n, 3));
	if (root > 0.0000001 && root < 1)
		return (1);
	return (0);
}

static int	my_shadow_sq(t_scene *sn, double *dir, double *p, int i)
{
	double	root;
	double	proj[2];
	double	vip[3];

	vector_sub_f(p, sn->shapes.sq[i].xyz, sn->shapes.sq[i].cp, 3);
	root = -(dot_f(sn->shapes.sq[i].cp, sn->shapes.sq[i].n, 3) /
			dot_f(dir, sn->shapes.sq[i].n, 3));
	if (root > 0.0000001 && root < 1)
	{
		vector_sub_f(p, sn->shapes.sq[sn->sqn].xyz, vip, 3);
		proj[0] = fabs(dot_f(vip, sn->shapes.sq[i].e1, 3));
		proj[1] = fabs(dot_f(vip, sn->shapes.sq[i].e2, 3));
		if ((proj[0] <= sn->shapes.sq[i].side && proj[0] >= 0) &&
				(proj[1] <= sn->shapes.sq[i].side && proj[1] >= 0))
			return (1);
	}
	return (0);
}

static int	my_shadow_tr(t_scene *sn, double *dir, double *p, int i)
{
	double	cross[3];
	double	vp[3];
	double	temp[7];

	vector_sub_f(p, sn->shapes.tr[i].c, sn->shapes.tr[i].cp, 3);
	temp[6] = -(dot_f(sn->shapes.tr[i].cp, sn->shapes.tr[i].n, 3) /
			dot_f(dir, sn->shapes.tr[i].n, 3));
	if (temp[6] < 0.0000001 || temp[6] > 1)
		return (0);
	vector_mult_f(temp[6], dir, temp, 3);
	vector_sub_f(p, sn->shapes.tr[i].a, sn->shapes.tr[i].cp, 3);
	vector_add_f(sn->shapes.tr[i].cp, temp, vp, 3);
	vec3_cross_f(vp, sn->shapes.tr[i].ab, cross);
	temp[3] = dot_f(cross, sn->shapes.tr[i].n, 3);
	vector_sub_f(p, sn->shapes.tr[i].b, sn->shapes.tr[i].cp, 3);
	vector_add_f(sn->shapes.tr[i].cp, temp, vp, 3);
	vec3_cross_f(vp, sn->shapes.tr[i].bc, cross);
	temp[4] = dot_f(cross, sn->shapes.tr[i].n, 3);
	vector_sub_f(p, sn->shapes.tr[i].c, sn->shapes.tr[i].cp, 3);
	vector_add_f(sn->shapes.tr[i].cp, temp, vp, 3);
	vec3_cross_f(vp, sn->shapes.tr[i].ca, cross);
	temp[5] = dot_f(cross, sn->shapes.tr[i].n, 3);
	if (temp[3] > 0 && temp[4] > 0 && temp[5] > 0)
		return (1);
	return (0);
}

int			shadow_calc(t_scene *scene, double *dir, double *p)
{
	int	i;

	i = -1;
	while (++i < scene->shapes.nsp)
		if (my_shadow_sp(scene, dir, p, i))
			return (1);
	i = -1;
	while (++i < scene->shapes.npl)
		if (my_shadow_pl(scene, dir, p, i))
			return (1);
	i = -1;
	while (++i < scene->shapes.nsq)
		if (my_shadow_sq(scene, dir, p, i))
			return (1);
	i = -1;
	while (++i < scene->shapes.ntr)
		if (my_shadow_tr(scene, dir, p, i))
			return (1);
	i = -1;
	while (++i < scene->shapes.ncy)
		if (shadow_cy(scene, dir, p, i))
			return (1);
	return (0);
}
