/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sp_pl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:22:44 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:36:24 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static void	my_new_sp(char *scene, t_sphere *sp)
{
	(sp->xyz)[0] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sp->xyz)[1] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sp->xyz)[2] = ft_atod(scene);
	scene = ft_strchr(scene, ' ');
	scene = skip_space(scene);
	sp->d = ft_atod(scene);
	scene = ft_strchr(scene, ' ') + 1;
	(sp->rgb)[0] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sp->rgb)[1] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	(sp->rgb)[2] = ft_atoi(scene);
}

void		get_sp(char **scene, t_scene *out)
{
	t_sphere	*temp;
	int			i;

	while (*scene)
	{
		if (ft_strncmp(*scene, "sp", 2) == 0)
		{
			(out->shapes).nsp += 1;
			if (!(temp = (t_sphere*)malloc(sizeof(t_sphere) *
											(out->shapes).nsp)))
				perr_handle();
			i = -1;
			while (++i < (out->shapes).nsp - 1)
				temp[i] = ((out->shapes).sp)[i];
			my_new_sp(*scene + 2, &temp[i]);
			free((out->shapes).sp);
			out->shapes.sp = temp;
		}
		scene++;
	}
}

static void	my_new_pl(char *scene, t_plane *pl)
{
	(pl->xyz)[0] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(pl->xyz)[1] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(pl->xyz)[2] = ft_atod(scene);
	scene = ft_strchr(scene, ' ');
	scene = skip_space(scene);
	(pl->n)[0] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(pl->n)[1] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(pl->n)[2] = ft_atod(scene);
	scene = ft_strchr(scene, ' ') + 1;
	(pl->rgb)[0] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	(pl->rgb)[1] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	pl->rgb[2] = ft_atoi(scene);
}

void		get_pl(char **scene, t_scene *out)
{
	t_plane *temp;
	int		i;

	while (*scene)
	{
		if (ft_strncmp(*scene, "pl", 2) == 0)
		{
			(out->shapes).npl += 1;
			if (!(temp = (t_plane*)malloc(sizeof(t_plane) * (out->shapes).npl)))
				perr_handle();
			i = -1;
			while (++i < (out->shapes).npl - 1)
				temp[i] = ((out->shapes).pl)[i];
			my_new_pl(*scene + 2, &temp[i]);
			free(out->shapes.pl);
			out->shapes.pl = temp;
		}
		scene++;
	}
}
