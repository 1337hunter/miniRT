/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_window_n_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 00:12:14 by student           #+#    #+#             */
/*   Updated: 2020/07/03 12:38:12 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"

static void	my_make_hooks(void *wptr, t_scene *sn)
{
	mlx_hook(wptr, 2, 1L << 0, key_press, sn);
	mlx_hook(wptr, 17, 1L << 17, exit_program, 0);
}

void		make_window_n_img(t_scene *sn, t_mlx *mlx, t_img *img)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, sn->w, sn->h, "THIS IS IT!");
	my_make_hooks(mlx->win_ptr, sn);
	img->img = mlx_new_image(mlx->mlx_ptr, sn->w, sn->h);
	img->data = mlx_get_data_addr(img->img, &(img->bpp), &(img->sl),
																&(img->en));
}
