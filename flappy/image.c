/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:05:11 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/05 16:05:30 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flapy.h"

t_img	new_img(int w, int h, t_game *window)
{
	t_img	image;

	image.win = window;
	image.img_ptr = mlx_new_image(window->mlx, w, h);
	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.line_len), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
}

t_img	new_file_img(char *path, t_game *window)
{
	t_img		image;
	static int	i;

	image.win = window;
	image.img_ptr = mlx_xpm_file_to_image(window->mlx,
			path, &image.w, &image.h);
	if (!image.img_ptr)
		write(2, "File could not be read\n", 23);
	else
		image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
				&(image.line_len), &(image.endian));
	i++;
	return (image);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000 || color == (int)0xADF802)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr
			+ (y * img.line_len) + (x * img.bpp / 8))));
}

void	put_img_to_img(t_img dst, t_img src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

void	put_nimg_to_img(t_img dst, t_img src, int x, int y, int w, int h)
{
	int	i;
	int	j;
	int	tmp;

	if (i > 150)
		i = w - 150;
	else
		i = 0;
	if (h > 120)
		j = h - 120;
	else
		j = 0;
	tmp = j;
	while (i < w)
	{
		j = tmp;
		while (j < h)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}