/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 08:47:45 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 12:08:25 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vec3_cross_f(double *v1, double *v2, double *res)
{
	res[0] = v1[1] * v2[2] - v1[2] * v2[1];
	res[1] = v1[2] * v2[0] - v1[0] * v2[2];
	res[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void	vec3_rejectf(double *v1, double *v2, double *res)
{
	double	b[3];

	vector_mult_f(dot_f(v1, v2, 3) / dot_f(v2, v2, 3), v2, b, 3);
	vector_sub_f(v1, b, res, 3);
}

void	get_up_vector(double *up, double *dir)
{
	up[0] = 0;
	up[1] = 0;
	up[2] = 0;
	if (dir[1] > 0.9 || dir[1] < -0.9)
		up[2] = 1;
	else
		up[1] = 1;
}
