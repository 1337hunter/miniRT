/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 16:37:37 by gbright           #+#    #+#             */
/*   Updated: 2020/05/07 17:26:24 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int			flag;
	long long	out;

	flag = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\r' ||
			*nptr == '\v' || *nptr == '\f' || *nptr == '\n')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			flag = -1;
		nptr++;
	}
	out = 0;
	while (*nptr <= '9' && *nptr >= '0')
	{
		if (out * flag * 10 < out * flag)
			return (flag < 0 ? 0 : -1);
		out *= 10;
		out += flag * (*nptr++ - '0');
	}
	return ((int)out);
}
