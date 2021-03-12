/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_deal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:40 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 14:16:01 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

void	light_calc_sp(double *p, double *n, t_scene *scene, double *ki)
{
	int		i;
	int		k;
	double	direction[3];
	double	dot_p;

	k = -1;
	while (++k < 3)
		ki[k] = scene->a->rgb[k] * scene->a->a / 255;
	k = -1;
	while (++k < scene->nl)
	{
		vector_sub_f((scene->l)[k].xyz, p, direction, 3);
		dot_p = dot_f(n, direction, 3);
		i = shadow_calc(scene, direction, p);
		if (dot_p > 0 && i == 0)
		{
			i = -1;
			while (++i < 3)
				ki[i] += ((scene->l)[k].l * dot_p / (vector_norm2_f(n, 3) *
	vector_norm2_f(direction, 3))) * ((double)(((scene->l)[k]).rgb[i]) / 255);
		}
	}
}

void	light_calc_pl(double *p, double *n, t_scene *sn)
{
	int		i;
	int		k;
	double	dir[3];
	double	dot_p;

	k = -1;
	while (++k < 3)
		sn->ki[k] = sn->a->rgb[k] * sn->a->a / 255;
	if (dot_f(sn->view, n, 3) > 0)
		vector_mult_f(-1, n, n, 3);
	k = -1;
	while (++k < sn->nl)
	{
		vector_sub_f(sn->l[k].xyz, p, dir, 3);
		dot_p = dot_f(n, dir, 3);
		i = shadow_calc(sn, dir, p);
		if (dot_p >= 0 && i == 0)
		{
			i = -1;
			while (++i < 3)
				sn->ki[i] += ((sn->l)[k].l * dot_p / (vector_norm2_f(n, 3) *
		vector_norm2_f(dir, 3))) * ((double)(((sn->l)[k]).rgb[i]) / 255);
		}
	}
}

void	light_calc_sq(double *p, double *n, t_scene *sn)
{
	int		i;
	int		k;
	double	dir[3];
	double	dot_p;

	k = -1;
	while (++k < 3)
		sn->ki[k] = sn->a->rgb[k] * sn->a->a / 255;
	if (dot_f(sn->view, n, 3) > 0)
		vector_mult_f(-1, n, n, 3);
	k = -1;
	while (++k < sn->nl)
	{
		vector_sub_f(sn->l[k].xyz, p, dir, 3);
		dot_p = dot_f(n, dir, 3);
		i = shadow_calc(sn, dir, p);
		if (dot_p > 0 && i == 0)
		{
			i = -1;
			while (++i < 3)
				sn->ki[i] += ((sn->l)[k].l * dot_p / (vector_norm2_f(n, 3) *
		vector_norm2_f(dir, 3))) * ((double)(((sn->l)[k]).rgb[i]) / 255);
		}
	}
}

void	light_calc_tr(double *p, double *n, t_scene *sn)
{
	int		k;
	double	dir[3];
	double	dot;
	int		i;
	double	tempn[3];

	k = -1;
	while (++k < 3)
	{
		tempn[k] = n[k];
		sn->ki[k] = sn->a->rgb[k] * sn->a->a / 255;
	}
	if (dot_f(sn->view, tempn, 3) < 0)
		vector_mult_f(-1, tempn, tempn, 3);
	k = -1;
	while (++k < sn->nl)
	{
		vector_sub_f(sn->l[k].xyz, p, dir, 3);
		dot = dot_f(tempn, dir, 3);
		i = -1;
		if (dot < 0 && !(shadow_calc(sn, dir, p)))
			while (++i < 3)
				sn->ki[i] += ((sn->l)[k].l * (-dot) / (vector_norm2_f(tempn, 3)
		* vector_norm2_f(dir, 3))) * ((double)(((sn->l)[k]).rgb[i]) / 255);
	}
}

void	light_calc_cy(double *p, double *n, t_scene *sn)
{
	int		k;
	double	dir[3];
	double	dot;
	int		i;

	k = -1;
	while (++k < 3)
		sn->ki[k] = sn->a->rgb[k] * sn->a->a / 255;
	if (dot_f(sn->view, n, 3) > 0)
		vector_mult_f(-1, n, n, 3);
	k = -1;
	while (++k < sn->nl)
	{
		vector_sub_f(sn->l[k].xyz, p, dir, 3);
		dot = dot_f(n, dir, 3);
		i = shadow_calc(sn, dir, p);
		if (dot > 0 && i == 0)
		{
			i = -1;
			while (++i < 3)
				sn->ki[i] += ((sn->l)[k].l * dot / (vector_norm2_f(n, 3) *
		vector_norm2_f(dir, 3))) * ((double)(((sn->l)[k]).rgb[i]) / 255);
		}
	}
}
