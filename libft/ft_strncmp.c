/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 14:59:11 by gbright           #+#    #+#             */
/*   Updated: 2020/05/05 15:40:43 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	ch1;

	i = -1;
	while (++i < n && (s1[i] != 0 || s2[i] != 0))
	{
		if (s1[i] != s2[i])
		{
			ch1 = ((unsigned char*)s1)[i];
			return (ch1 - ((unsigned char*)s2)[i]);
		}
	}
	return (0);
}
