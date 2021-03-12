/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_effects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 17:28:50 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 17:28:52 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

void	get_filter(char **sn, t_scene *out)
{
	while (*sn)
	{
		if (ft_strncmp(*sn, "SEPIA", 5) == 0)
		{
			out->sepia = 1;
			return ;
		}
		sn++;
	}
}
