/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:05:06 by gbright           #+#    #+#             */
/*   Updated: 2020/07/06 13:53:40 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*param;
}				t_mlx;

typedef	struct	s_img
{
	void		*img;
	char		*data;
	int			bpp;
	int			sl;
	int			en;
}				t_img;

typedef	struct	s_sphere
{
	double		xyz[3];
	double		pc[3];
	short		rgb[3];
	double		d;
	double		oc[3];

}				t_sphere;

typedef	struct	s_plane
{
	double		xyz[3];
	double		n[3];
	double		po[3];
	double		cp[3];
	short		rgb[3];
}				t_plane;

typedef struct	s_square
{
	double		xyz[3];
	double		n[3];
	double		up[3];
	double		e1[3];
	double		e2[3];
	double		op[3];
	double		cp[3];
	double		side;
	short		rgb[3];
}				t_square;

typedef struct	s_cylinder
{
	double		xyz[3];
	double		n[3];
	double		oc[3];
	double		cp[3];
	double		d;
	double		h;
	short		rgb[3];
}				t_cylinder;

typedef struct	s_triangle
{
	double		a[3];
	double		b[3];
	double		c[3];
	double		op[3];
	double		ab[3];
	double		bc[3];
	double		ca[3];
	double		n[3];
	double		cp[3];
	short		rgb[3];
}				t_triangle;

typedef struct	s_shapes
{
	short		nsp;
	short		npl;
	short		nsq;
	short		ncy;
	short		ntr;
	t_sphere	*sp;
	t_plane		*pl;
	t_square	*sq;
	t_cylinder	*cy;
	t_triangle	*tr;
}				t_shapes;

typedef	struct	s_ambient
{
	double		a;
	short		rgb[3];
}				t_ambient;

typedef struct	s_camera
{
	double		xyz[3];
	double		n[3];
	double		vw;
	double		vh;
	double		d;
	short		fov;
}				t_camera;

typedef struct	s_light
{
	double		xyz[3];
	double		l;
	short		rgb[3];
}				t_light;

typedef struct	s_scene
{
	int			w;
	int			h;
	int			na;
	int			nc;
	int			nl;
	int			spn;
	int			pln;
	int			sqn;
	int			trn;
	int			cyn;
	unsigned	cu;
	double		closest;
	double		shadow;
	short		color[3];
	double		ki[3];
	t_mlx		*mlx;
	t_img		*img;
	double		view[3];
	short		save;
	short		sepia;
	t_ambient	*a;
	t_camera	*c;
	t_light		*l;
	t_shapes	shapes;
}				t_scene;

int				exit_program(void *param);
int				key_press(int keycode, void *param);
void			control(char **av, int ac);
void			make_window_n_img(t_scene *scene, t_mlx *mlx, t_img *img);
t_scene			*get_scene(char **av);
int				perr_handle(void);
void			err_scene(char **scene);
void			error_cy(char *cy);
void			error_sq(char *sq);
void			error_tr(char *tr);
char			*check_vector(char *v);
void			deep_scene_error(char **scene);
int				save_bmp(const char *fname, int *img_data, int mx, int my);
void			make_shapes(t_mlx mlx, t_img img);
t_scene			*parse_scene(char **scene);
char			*skip_space(char *input);
char			*skip_float(char *input);
void			exit_status(char *errline);
void			get_amb(char **scene, t_scene *out);
void			get_light(char **scene, t_scene *out);
void			get_sp(char **scene, t_scene *out);
void			get_pl(char **scene, t_scene *out);
void			get_sq(char **scene, t_scene *out);
void			get_cy(char **scene, t_scene *out);
void			get_tr(char **scene, t_scene *out);
void			get_filter(char **scene, t_scene *out);
void			rendering(t_scene *scene, t_img *img, t_mlx *mlx);
void			intersect_sp(t_scene *scene);
void			intersect_pl(t_scene *scene);
void			intersect_sq(t_scene *scene);
void			intersect_tr(t_scene *scene);
void			intersect_cy(t_scene *scene);
double			dot_f(double *v1, double *v2, int len);
void			vector_sub_f(double *v1, double *v2, double *res, int len);
void			vector_mult_f(double k, double *v2, double *res, int len);
void			vector_add_f(double *v1, double *v2, double *res, int len);
double			vector_norm2_f(double *v, int len);
void			vec3_cross_f(double *v1, double *v2, double *res);
void			vec3_rejectf(double *v1, double *v2, double *res);
void			get_up_vector(double *up, double *dir);
void			viewport_xyz(t_scene *scene, int x, int y);
int				get_color(short *rgb);
void			set_color(short *out, short r, short g, short b);
void			light_calc_sp(double *p, double *n, t_scene *scene, double *ki);
void			light_calc_pl(double *p, double *n, t_scene *sn);
void			light_calc_sq(double *p, double *n, t_scene *sn);
void			light_calc_tr(double *p, double *n, t_scene *sn);
void			light_calc_cy(double *p, double *n, t_scene *sn);
void			color_check(t_scene *sn);
void			color_intensity(short *color, double *ki);
void			sepia(short *rgb);
int				shadow_calc(t_scene *scene, double *dir, double *p);
int				shadow_cy(t_scene *scene, double *dir, double *p, int i);
#endif
