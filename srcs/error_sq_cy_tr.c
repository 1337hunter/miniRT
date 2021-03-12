/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_sq_cy_tr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:21:41 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:29:23 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_sq(char *sq)
{
	if (*sq != ' ')
		exit_status("Error\nSquare error\n");
	if (!(sq = check_vector(sq)))
		exit_status("Error\nSquare error\n");
	if (!(sq = check_vector(sq)))
		exit_status("Error\nSquare error\n");
	sq = skip_space(sq);
	if ((*sq < '0' || *sq > '9') && *sq != '-' && *sq != '+')
		exit_status("Error\nSquare error\n");
	sq = skip_float(sq);
	if (!(sq = check_vector(sq)))
		exit_status("Error\nSquare error\n");
}

void	error_cy(char *cy)
{
	if (*cy != ' ')
		exit_status("Error\nCylinder error\n");
	if (!(cy = check_vector(cy)))
		exit_status("Error\nCylinder error\n");
	if (!(cy = check_vector(cy)))
		exit_status("Error\nCylinder error\n");
	cy = skip_space(cy);
	if ((*cy < '0' || *cy > '9') && *cy != '-' && *cy != '+')
		exit_status("Error\nCylinder error\n");
	cy = skip_float(cy);
	cy = skip_space(cy);
	if ((*cy < '0' || *cy > '9') && *cy != '-' && *cy != '+')
		exit_status("Error\nCylinder error\n");
	cy = skip_float(cy);
	if (!(cy = check_vector(cy)))
		exit_status("Error\nCylinder error\n");
}

void	error_tr(char *tr)
{
	if (*tr != ' ')
		exit_status("Error\nTriangle error\n");
	if (!(tr = check_vector(tr)))
		exit_status("Error\nTriangle error\n");
	if (!(tr = check_vector(tr)))
		exit_status("Error\nTriangle error\n");
	if (!(tr = check_vector(tr)))
		exit_status("Error\nTriangle error\n");
	if (!(tr = check_vector(tr)))
		exit_status("Error\nTriangle error\n");
}
