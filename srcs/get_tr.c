/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:22:56 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 16:04:56 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static char	*my_get_vector(char *s, double *vec)
{
	vec[0] = ft_atod(s);
	s = ft_strchr(s, ',') + 1;
	vec[1] = ft_atod(s);
	s = ft_strchr(s, ',') + 1;
	vec[2] = ft_atod(s);
	s = ft_strchr(s, ' ');
	return (s);
}

static void	my_new_tr(char *scene, t_triangle *tr)
{
	scene = my_get_vector(scene, tr->a);
	scene = my_get_vector(scene, tr->b);
	scene = my_get_vector(scene, tr->c);
	tr->rgb[0] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	tr->rgb[1] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	tr->rgb[2] = ft_atoi(scene);
	vector_sub_f(tr->b, tr->a, tr->ab, 3);
	vector_sub_f(tr->c, tr->b, tr->bc, 3);
	vector_sub_f(tr->a, tr->c, tr->ca, 3);
	vec3_cross_f(tr->ab, tr->ca, tr->n);
	vector_mult_f(1 / vector_norm2_f(tr->n, 3), tr->n, tr->n, 3);
}

void		get_tr(char **scene, t_scene *out)
{
	t_triangle	*temp;
	int			i;

	while (*scene)
	{
		if (ft_strncmp(*scene, "tr", 2) == 0)
		{
			out->shapes.ntr += 1;
			if (!(temp = (t_triangle*)malloc(sizeof(t_triangle) *
												out->shapes.ntr)))
				perr_handle();
			i = -1;
			while (++i < out->shapes.ntr - 1)
				temp[i] = (out->shapes.tr)[i];
			my_new_tr(*scene + 2, &temp[i]);
			free(out->shapes.tr);
			out->shapes.tr = temp;
		}
		scene++;
	}
}
