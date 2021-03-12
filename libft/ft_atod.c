/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:56:54 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:57:10 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(char *a)
{
	double	d;
	double	div;
	double	sign;

	d = (double)ft_atoi(a);
	while (*a == ' ' || *a == '\t' || *a == '\r' || *a == '\v' ||
			*a == '\f' || *a == '\n')
		a++;
	sign = 1;
	if (*a == '+' || *a == '-')
	{
		sign = (*a == '-' ? -1.0 : 1.0);
		a++;
	}
	while (*a >= '0' && *a <= '9')
		a++;
	div = 1;
	if (*a++ == '.')
		while (*a >= '0' && *a <= '9' && (div *= 10))
			d += sign * (*a++ - '0') / div;
	return (d);
}