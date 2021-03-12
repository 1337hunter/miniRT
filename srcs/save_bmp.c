/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:27:16 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:46:04 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static void	my_record_img(unsigned char *img, int *img_data, int w, int h)
{
	int				i;
	int				size;
	unsigned char	*img_data_ptr;

	size = 3 * h * w;
	i = 0;
	img_data_ptr = (unsigned char*)img_data;
	while (i < size)
	{
		img[i] = *(img_data_ptr);
		img[i + 1] = *(img_data_ptr + 1);
		img[i + 2] = *(img_data_ptr + 2);
		i += 3;
		img_data_ptr++;
		img_data_ptr += 3;
	}
}

static void	my_not_enough(unsigned char *iheader)
{
	iheader[0] = 40;
	iheader[12] = 1;
	iheader[14] = 24;
}

static void	my_fill_header(int fd, int w, int h)
{
	int				fsize;
	unsigned char	fheader[14];
	unsigned char	iheader[40];

	fsize = 54 + 3 * w * h;
	ft_memset(fheader, 0, 14);
	ft_memset(iheader, 0, 40);
	fheader[0] = 'B';
	fheader[1] = 'M';
	fheader[2] = (unsigned char)(fsize);
	fheader[3] = (unsigned char)(fsize >> 8);
	fheader[4] = (unsigned char)(fsize >> 16);
	fheader[5] = (unsigned char)(fsize >> 24);
	fheader[10] = 54;
	my_not_enough(iheader);
	iheader[4] = (unsigned char)w;
	iheader[5] = (unsigned char)(w >> 8);
	iheader[6] = (unsigned char)(w >> 16);
	iheader[7] = (unsigned char)(w >> 24);
	iheader[8] = (unsigned char)h;
	iheader[9] = (unsigned char)(h >> 8);
	iheader[10] = (unsigned char)(h >> 16);
	iheader[11] = (unsigned char)(h >> 24);
	write(fd, fheader, 14);
	write(fd, iheader, 40);
}

static void	my_record_bmp(int fd, unsigned char *img, int w, int h)
{
	unsigned char	pad[3];
	int				i;

	ft_memset(pad, 0, 3);
	i = -1;
	while (++i < h)
	{
		write(fd, img + (w * (h - i - 1) * 3), w * 3);
		write(fd, pad, (4 - (w * 3) % 4) % 4);
	}
	free(img);
	close(fd);
}

int			save_bmp(const char *fname, int *img_data, int w, int h)
{
	int				fd;
	unsigned char	*img;
	int				fsize;

	fsize = 54 + 3 * w * h;
	if (!(img = (unsigned char*)malloc(3 * h * w)))
		perr_handle();
	ft_memset(img, 0, 3 * w * h);
	my_record_img(img, img_data, w, h);
	fd = open(fname, O_RDWR | O_CREAT, 0644);
	my_fill_header(fd, w, h);
	my_record_bmp(fd, img, w, h);
	return (0);
}
