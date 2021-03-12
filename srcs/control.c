/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:21:23 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:21:24 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "libft.h"

void	control(char **av, int ac)
{
	t_scene	*scene;
	t_mlx	*mlx;
	t_img	*img;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		perr_handle();
	if (!(img = (t_img*)malloc(sizeof(t_img))))
		perr_handle();
	scene = get_scene(av);
	if (ac == 3 && ft_strncmp(av[2], "--save", 6) == 0)
		scene->save = 1;
	make_window_n_img(scene, mlx, img);
	scene->mlx = mlx;
	scene->img = img;
	rendering(scene, img, mlx);
	if (!(scene->save))
		mlx_loop(mlx->mlx_ptr);
	exit(0);
}
