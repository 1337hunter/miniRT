/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_cy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:27:26 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 12:06:56 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	my_roots_cy(t_scene *sn, double *r, double *dir, int i)
{
	double	det;
	double	dxn[3];
	double	cpxn[3];
	double	coef[3];

	vec3_cross_f(dir, sn->shapes.cy[i].n, dxn);
	vec3_cross_f(sn->shapes.cy[i].cp, sn->shapes.cy[i].n, cpxn);
	coef[0] = dot_f(dxn, dxn, 3);
	coef[1] = 2 * dot_f(cpxn, dxn, 3);
	coef[2] = dot_f(cpxn, cpxn, 3) - sn->shapes.cy[i].d *
		sn->shapes.cy[i].d / 4;
	det = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (det < 0)
		return (1);
	r[0] = (-coef[1] + sqrt(det)) / (2 * coef[0]);
	r[1] = (-coef[1] - sqrt(det)) / (2 * coef[0]);
	return (0);
}

int			shadow_cy(t_scene *sn, double *dir, double *p, int i)
{
	double	r[2];
	double	inters[3];
	double	proj;

	vector_sub_f(p, sn->shapes.cy[i].xyz, sn->shapes.cy[i].cp, 3);
	if (my_roots_cy(sn, r, dir, i))
		return (0);
	vector_mult_f(r[0], dir, inters, 3);
	vector_add_f(p, inters, inters, 3);
	vector_sub_f(inters, sn->shapes.cy[i].xyz, inters, 3);
	proj = dot_f(inters, sn->shapes.cy[i].n, 3);
	if (proj > sn->shapes.cy[i].h || proj < 0)
		r[0] = 1.0 / 0.0;
	vector_mult_f(r[1], dir, inters, 3);
	vector_add_f(p, inters, inters, 3);
	vector_sub_f(inters, sn->shapes.cy[i].xyz, inters, 3);
	proj = dot_f(inters, sn->shapes.cy[i].n, 3);
	if (proj > sn->shapes.cy[i].h || proj < 0)
		r[1] = 1.0 / 0.0;
	if (r[0] > 0.0001 && r[0] < 1)
		return (1);
	if (r[1] > 0.0001 && r[1] < 1)
		return (1);
	return (0);
}
