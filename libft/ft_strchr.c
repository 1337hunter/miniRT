/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 01:40:33 by gbright           #+#    #+#             */
/*   Updated: 2020/05/01 13:45:02 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
		if (s[i] == (char)c)
			return (&((char*)s)[i]);
	if (s[i] == (char)c)
		return (&((char*)s)[i]);
	else
		return (0);
	return (0);
}
