/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_amb_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:22:13 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:22:14 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static void	my_new_amb(char *scene, t_ambient *amb)
{
	scene++;
	amb->a = ft_atod(scene);
	scene = skip_space(scene) + 1;
	while (*scene++ != ' ')
		;
	(amb->rgb)[0] = ft_atoi(scene);
	while (*scene++ != ',')
		;
	(amb->rgb)[1] = ft_atoi(scene);
	while (*scene++ != ',')
		;
	(amb->rgb)[2] = ft_atoi(scene);
}

void		get_amb(char **scene, t_scene *out)
{
	t_ambient	*temp;
	int			i;

	while (*scene)
	{
		if (**scene == 'A')
		{
			out->na += 1;
			if (!(temp = (t_ambient*)malloc(sizeof(t_ambient) * out->na)))
				perr_handle();
			i = -1;
			while (++i < out->na - 1)
				temp[i] = (out->a)[i];
			my_new_amb(*scene, &temp[i]);
			free(out->a);
			out->a = temp;
		}
		scene++;
	}
}

static void	my_new_light(char *scene, t_light *light)
{
	(light->xyz)[0] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(light->xyz)[1] = ft_atod(scene);
	scene = ft_strchr(scene, ',') + 1;
	(light->xyz)[2] = ft_atod(scene);
	scene = ft_strchr(scene, ' ');
	scene = skip_space(scene);
	light->l = ft_atod(scene);
	scene = ft_strchr(scene, ' ') + 1;
	(light->rgb)[0] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	(light->rgb)[1] = ft_atoi(scene);
	scene = ft_strchr(scene, ',') + 1;
	(light->rgb)[2] = ft_atoi(scene);
}

void		get_light(char **scene, t_scene *out)
{
	t_light	*temp;
	int		i;

	while (*scene)
	{
		if (ft_strncmp(*scene, "l ", 2) == 0)
		{
			out->nl += 1;
			if (!(temp = (t_light*)malloc(sizeof(t_light) * out->nl)))
				perr_handle();
			i = -1;
			while (++i < out->nl - 1)
				temp[i] = (out->l)[i];
			my_new_light(*scene + 1, &temp[i]);
			free(out->l);
			out->l = temp;
		}
		scene++;
	}
}
