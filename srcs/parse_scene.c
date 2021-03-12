/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 08:37:44 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 13:46:51 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static void	my_new_cam(char *scene, t_camera *cam)
{
	(cam->xyz)[0] = ft_atod(scene);
	while (*scene++ != ',')
		;
	(cam->xyz)[1] = ft_atod(scene);
	while (*scene++ != ',')
		;
	(cam->xyz)[2] = ft_atod(scene);
	while (*scene++ != ' ')
		;
	scene = skip_space(scene);
	(cam->n)[0] = ft_atod(scene);
	while (*scene++ != ',')
		;
	(cam->n)[1] = ft_atod(scene);
	while (*scene++ != ',')
		;
	(cam->n)[2] = ft_atod(scene);
	while (*scene++ != ' ')
		;
	cam->fov = ft_atoi(scene);
	cam->d = 1;
}

static void	my_get_cam(char **scene, t_scene *out)
{
	t_camera	*temp;
	int			i;

	while (*scene)
	{
		if (ft_strncmp(*scene, "c ", 2) == 0)
		{
			out->nc += 1;
			if (!(temp = (t_camera*)malloc(sizeof(t_camera) * out->nc)))
				perr_handle();
			i = -1;
			while (++i < out->nc - 1)
				temp[i] = (out->c)[i];
			my_new_cam(*scene + 1, &temp[i]);
			temp[i].vw = tan((temp[i].fov * (M_PI / 180)) / 2) * temp[i].d;
			temp[i].vh = temp[i].vw * out->h / out->w;
			vector_mult_f(1 / vector_norm2_f(temp[i].n, 3),
										temp[i].n, temp[i].n, 3);
			free(out->c);
			out->c = temp;
		}
		scene++;
	}
}

static void	my_get_res(char **scene, t_scene *out)
{
	char	*temp;

	while (**scene != 'R')
		scene++;
	temp = *scene + 1;
	while (*temp == ' ' && *temp)
		temp++;
	out->w = ft_atoi(temp);
	while (*temp >= '0' && *temp <= '9' && *temp)
		temp++;
	out->h = ft_atoi(temp);
	if (out->w < 0 || out->h < 0)
		exit_status("Error\nWidth or height is negative\n");
	out->w = (out->w > 2560 || out->w < 0 ? 2560 : out->w);
	out->h = (out->h > 1440 || out->h < 0 ? 1440 : out->h);
}

t_scene		*parse_scene(char **scene)
{
	t_scene	*out;

	if (!(out = (t_scene*)malloc(sizeof(t_scene))))
		perr_handle();
	ft_bzero(out, sizeof(t_scene));
	my_get_res(scene, out);
	my_get_cam(scene, out);
	get_amb(scene, out);
	get_light(scene, out);
	get_sp(scene, out);
	get_pl(scene, out);
	get_sq(scene, out);
	get_cy(scene, out);
	get_tr(scene, out);
	get_filter(scene, out);
	return (out);
}
