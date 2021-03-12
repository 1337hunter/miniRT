/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sp_pl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:04:40 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 12:04:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

void		viewport_xyz(t_scene *sn, int x, int y)
{
	double	right[3];
	double	up[3];
	double	temp[3];

	get_up_vector(temp, sn->c[sn->cu].n);
	vec3_cross_f(temp, sn->c[sn->cu].n, right);
	vec3_cross_f(sn->c[sn->cu].n, right, up);
	ft_bzero(sn->view, 3 * sizeof(double));
	vector_mult_f(x * (sn->c[sn->cu].vw / sn->w), right, temp, 3);
	vector_add_f(temp, sn->view, sn->view, 3);
	vector_mult_f(y * (sn->c[sn->cu].vh / sn->h), up, temp, 3);
	vector_add_f(temp, sn->view, sn->view, 3);
	vector_add_f(sn->c[sn->cu].n, sn->view, sn->view, 3);
}

static void	my_lighting_sp(t_scene *scene, double solution)
{
	double	p[3];
	double	n[3];
	double	tempd[3];

	scene->closest = solution;
	vector_mult_f(solution, scene->view, tempd, 3);
	vector_add_f(scene->c[scene->cu].xyz, tempd, p, 3);
	vector_sub_f(p, (scene->shapes.sp)[scene->spn].xyz, n, 3);
	vector_mult_f(1 / vector_norm2_f(n, 3), n, n, 3);
	light_calc_sp(p, n, scene, scene->ki);
	ft_memcpy(scene->color, scene->shapes.sp[scene->spn].rgb, 3 *
														sizeof(short));
}

void		intersect_sp(t_scene *sn)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root[2];

	a = dot_f(sn->view, sn->view, 3);
	b = 2 * dot_f(((sn->shapes.sp)[sn->spn]).oc, sn->view, 3);
	c = dot_f(((sn->shapes.sp)[sn->spn]).oc, ((sn->shapes.sp)[sn->spn]).oc, 3) -
		(sn->shapes.sp[sn->spn]).d * (sn->shapes.sp)[sn->spn].d / 4;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	root[0] = (-b + sqrt(discriminant)) / (2 * a);
	root[1] = (-b - sqrt(discriminant)) / (2 * a);
	if (root[0] < root[1] && root[0] > sn->c[sn->cu].d && root[0] < sn->closest)
		my_lighting_sp(sn, root[0]);
	if (root[1] < root[0] && root[1] > sn->c[sn->cu].d && root[1] < sn->closest)
		my_lighting_sp(sn, root[1]);
}

static void	my_lighting_pl(t_scene *sn, double root)
{
	double	p[3];
	double	tempd[3];

	sn->closest = root;
	vector_mult_f(root, sn->view, tempd, 3);
	vector_add_f(sn->c[sn->cu].xyz, tempd, p, 3);
	light_calc_pl(p, sn->shapes.pl[sn->pln].n, sn);
	ft_memcpy(sn->color, sn->shapes.pl[sn->pln].rgb, 3 * sizeof(short));
}

void		intersect_pl(t_scene *sn)
{
	double	root;

	vector_mult_f(1 / vector_norm2_f(sn->shapes.pl[sn->pln].n, 3),
			sn->shapes.pl[sn->pln].n, sn->shapes.pl[sn->pln].n, 3);
	root = -(dot_f(sn->shapes.pl[sn->pln].po, sn->shapes.pl[sn->pln].n, 3) /
		dot_f(sn->view, sn->shapes.pl[sn->pln].n, 3));
	if (root > sn->c[sn->cu].d && root < sn->closest)
		my_lighting_pl(sn, root);
}
