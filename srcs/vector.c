/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:27:48 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 12:08:08 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	dot_f(double *v1, double *v2, int len)
{
	double	res;

	res = 0;
	while (--len >= 0)
		res += v1[len] * v2[len];
	return (res);
}

void	vector_sub_f(double *v1, double *v2, double *res, int len)
{
	while (--len >= 0)
		res[len] = v1[len] - v2[len];
}

void	vector_mult_f(double k, double *v, double *res, int len)
{
	while (--len >= 0)
		res[len] = k * v[len];
}

double	vector_norm2_f(double *v, int len)
{
	double	res;

	res = 0;
	while (--len >= 0)
		res += pow(v[len], 2);
	return (sqrt(res));
}

void	vector_add_f(double *v1, double *v2, double *res, int len)
{
	while (--len >= 0)
		res[len] = v1[len] + v2[len];
}
