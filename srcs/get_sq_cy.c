/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sq_cy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:22:33 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 17:22:07 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static void	my_new_sq(char *scene, t_square *sq)
{
	(sq->xyz)[0] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sq->xyz)[1] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sq->xyz)[2] = ft_atod(scene);
	scene = ft_strchr(scene, ' ') + 1;
	(sq->n)[0] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sq->n)[1] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sq->n)[2] = ft_atod(scene);
	scene = ft_strchr(scene, ' ');
	scene = skip_space(scene);
	sq->side = ft_atod(scene);
	scene = ft_strchr(scene, ' ') + 1;
	(sq->rgb)[0] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sq->rgb)[1] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sq->rgb)[2] = ft_atoi(scene);
	vector_mult_f(1 / vector_norm2_f(sq->n, 3), sq->n, sq->n, 3);
	get_up_vector(sq->up, sq->n);
	vec3_cross_f(sq->up, sq->n, sq->e1);
	vec3_cross_f(sq->n, sq->e1, sq->e2);
}

void		get_sq(char **scene, t_scene *out)
{
	t_square	*temp;
	int			i;

	while (*scene)
	{
		if (ft_strncmp(*scene, "sq", 2) == 0)
		{
			out->shapes.nsq += 1;
			if (!(temp = (t_square*)malloc(sizeof(t_square) * out->shapes.nsq)))
				perr_handle();
			i = -1;
			while (++i < out->shapes.nsq - 1)
				temp[i] = (out->shapes.sq)[i];
			my_new_sq(*scene + 2, &temp[i]);
			vector_mult_f(1 / vector_norm2_f(temp[i].e1, 3), temp[i].e1,
					temp[i].e1, 3);
			vector_mult_f(1 / vector_norm2_f(temp[i].e1, 3), temp[i].e1,
					temp[i].e1, 3);
			temp[i].side = temp[i].side / 2;
			free(out->shapes.sq);
			out->shapes.sq = temp;
		}
		scene++;
	}
}

static void	my_new_cy(char *scene, t_cylinder *cy)
{
	(cy->xyz)[0] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(cy->xyz)[1] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(cy->xyz)[2] = ft_atod(scene);
	scene = ft_strchr(scene, ' ') + 1;
	(cy->n)[0] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(cy->n)[1] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(cy->n)[2] = ft_atod(scene);
	scene = ft_strchr(scene, ' ');
	scene = skip_space(scene);
	cy->d = ft_atod(scene);
	scene = ft_strchr(scene, ' ');
	scene = skip_space(scene);
	cy->h = ft_atod(scene);
	scene = ft_strchr(scene, ' ') + 1;
	(cy->rgb)[0] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	(cy->rgb)[1] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	(cy->rgb)[2] = ft_atoi(scene);
	vector_mult_f(1 / vector_norm2_f(cy->n, 3), cy->n, cy->n, 3);
}

void		get_cy(char **scene, t_scene *out)
{
	t_cylinder	*temp;
	int			i;

	while (*scene)
	{
		if (ft_strncmp(*scene, "cy", 2) == 0)
		{
			out->shapes.ncy += 1;
			if (!(temp = (t_cylinder*)malloc(sizeof(t_cylinder) *
							out->shapes.ncy)))
				perr_handle();
			i = -1;
			while (++i < out->shapes.ncy - 1)
				temp[i] = (out->shapes.cy)[i];
			my_new_cy(*scene + 2, &temp[i]);
			free(out->shapes.cy);
			out->shapes.cy = temp;
		}
		scene++;
	}
}
