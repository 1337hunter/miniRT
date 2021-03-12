/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sq_tr_cy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:25:59 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 16:03:30 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

void		intersect_sq(t_scene *sn)
{
	double	proj[2];
	double	root;
	double	p[3];
	double	dir[3];
	double	vip[3];

	root = -(dot_f(sn->shapes.sq[sn->sqn].op, sn->shapes.sq[sn->sqn].n, 3) /
			dot_f(sn->view, sn->shapes.sq[sn->sqn].n, 3));
	if (root < sn->closest)
	{
		vector_mult_f(root, sn->view, dir, 3);
		vector_add_f(sn->c[sn->cu].xyz, dir, p, 3);
		vector_sub_f(p, sn->shapes.sq[sn->sqn].xyz, vip, 3);
		proj[0] = fabs(dot_f(vip, sn->shapes.sq[sn->sqn].e1, 3));
		proj[1] = fabs(dot_f(vip, sn->shapes.sq[sn->sqn].e2, 3));
		if ((proj[0] < sn->shapes.sq[sn->sqn].side && proj[0] >= 0) &&
				(proj[1] < sn->shapes.sq[sn->sqn].side && proj[1] >= 0))
		{
			sn->closest = root;
			light_calc_sq(p, sn->shapes.sq[sn->sqn].n, sn);
			ft_memcpy(sn->color, sn->shapes.sq[sn->sqn].rgb, 3 * sizeof(short));
		}
	}
}

void		intersect_tr(t_scene *sn)
{
	double	p[3];
	double	cross[3];
	double	vp[4];

	vp[3] = -(dot_f(sn->shapes.tr[sn->trn].op, sn->shapes.tr[sn->trn].n, 3) /
			dot_f(sn->view, sn->shapes.tr[sn->trn].n, 3));
	if (vp[3] >= sn->closest || vp[3] <= -25000)
		return ;
	vector_mult_f(vp[3], sn->view, p, 3);
	vector_add_f(sn->c[sn->cu].xyz, p, p, 3);
	vector_sub_f(p, sn->shapes.tr[sn->trn].a, vp, 3);
	vec3_cross_f(vp, sn->shapes.tr[sn->trn].ab, cross);
	if (dot_f(cross, sn->shapes.tr[sn->trn].n, 3) < -0.00001)
		return ;
	vector_sub_f(p, sn->shapes.tr[sn->trn].b, vp, 3);
	vec3_cross_f(vp, sn->shapes.tr[sn->trn].bc, cross);
	if (dot_f(cross, sn->shapes.tr[sn->trn].n, 3) < -0.00001)
		return ;
	vector_sub_f(p, sn->shapes.tr[sn->trn].c, vp, 3);
	vec3_cross_f(vp, sn->shapes.tr[sn->trn].ca, cross);
	if (dot_f(cross, sn->shapes.tr[sn->trn].n, 3) < -0.0001)
		return ;
	sn->closest = vp[3];
	light_calc_tr(p, sn->shapes.tr[sn->trn].n, sn);
	ft_memcpy(sn->color, sn->shapes.tr[sn->trn].rgb, 3 * sizeof(short));
}

static int	my_calc_roots(t_scene *sn, double *root)
{
	double	det;
	double	dxn[3];
	double	ocxn[3];
	double	coef[3];

	vec3_cross_f(sn->view, sn->shapes.cy[sn->cyn].n, dxn);
	vec3_cross_f(sn->shapes.cy[sn->cyn].oc, sn->shapes.cy[sn->cyn].n, ocxn);
	coef[0] = dot_f(dxn, dxn, 3);
	coef[1] = 2 * dot_f(ocxn, dxn, 3);
	coef[2] = dot_f(ocxn, ocxn, 3) - sn->shapes.cy[sn->cyn].d *
		sn->shapes.cy[sn->cyn].d / 4;
	det = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (det < 0)
		return (1);
	root[0] = (-coef[1] + sqrt(det)) / (2 * coef[0]);
	root[1] = (-coef[1] - sqrt(det)) / (2 * coef[0]);
	return (0);
}

static int	my_intersect_cy(t_scene *sn, double *root, double *p)
{
	double	proj;

	if (my_calc_roots(sn, root))
		return (1);
	vector_mult_f(root[0], sn->view, p, 3);
	vector_add_f(sn->c[sn->cu].xyz, p, p, 3);
	vector_sub_f(p, sn->shapes.cy[sn->cyn].xyz, sn->shapes.cy[sn->cyn].cp, 3);
	proj = dot_f(sn->shapes.cy[sn->cyn].cp, sn->shapes.cy[sn->cyn].n, 3);
	if ((proj > sn->shapes.cy[sn->cyn].h || proj < 0))
		root[0] = 1.0 / 0.0;
	vector_mult_f(root[1], sn->view, p, 3);
	vector_add_f(sn->c[sn->cu].xyz, p, p, 3);
	vector_sub_f(p, sn->shapes.cy[sn->cyn].xyz, sn->shapes.cy[sn->cyn].cp, 3);
	proj = dot_f(sn->shapes.cy[sn->cyn].cp, sn->shapes.cy[sn->cyn].n, 3);
	if ((proj > sn->shapes.cy[sn->cyn].h || proj < 0) && root[0] != 0)
		root[1] = 1.0 / 0.0;
	return (0);
}

void		intersect_cy(t_scene *sn)
{
	double	normal[3];
	double	r[4];
	double	p[3];
	double	t;

	t = 0.0 / 0.0;
	if (my_intersect_cy(sn, r, p))
		return ;
	if (r[0] > sn->c[sn->cu].d && r[0] < sn->closest && r[0] < r[1])
		t = r[0];
	if (r[1] > sn->c[sn->cu].d && r[1] < sn->closest && r[1] < r[0])
		t = r[1];
	if (t != r[0] && t != r[1])
		return ;
	vector_mult_f(t, sn->view, p, 3);
	vector_add_f(sn->c[sn->cu].xyz, p, p, 3);
	vector_sub_f(p, sn->shapes.cy[sn->cyn].xyz, sn->shapes.cy[sn->cyn].cp, 3);
	sn->closest = t;
	r[3] = dot_f(sn->shapes.cy[sn->cyn].cp, sn->shapes.cy[sn->cyn].n, 3);
	vector_mult_f(r[3], sn->shapes.cy[sn->cyn].n, normal, 3);
	vector_sub_f(sn->shapes.cy[sn->cyn].cp, normal, normal, 3);
	light_calc_cy(p, normal, sn);
	ft_memcpy(sn->color, sn->shapes.cy[sn->cyn].rgb, 3 * sizeof(short));
}
