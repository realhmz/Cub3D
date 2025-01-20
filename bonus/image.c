#include "cub.h"

t_img	new_img(int w, int h, t_game *game)
{
	t_img	image;

	image.win = game;
	image.img_ptr = mlx_new_image(game->mlx, w, h);
	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.line_len), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
}

t_img	new_file_img(char *path, t_game *game)
{
	t_img		image;
	static int	i;

	image.win = game;
	image.img_ptr = mlx_xpm_file_to_image(game->mlx,
			path, &image.w, &image.h);
	if (!image.img_ptr)
		write(2, "File could not be read\n", 23);
	else
		image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
				&(image.line_len), &(image.endian));
	i++;
	return (image);
}

t_img	new_file_img_safe(char *path, t_game *game)
{
	t_img		image;
	static int	i;

	image.win = game;
	image.img_ptr = read_xpm_safely(game->mlx, &image.w, &image.h);
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

	if (color == (int)0xFF000000 || ! color)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	if (x > img.line_len || y > img.h)
	{
		return 120;
	}
	return (*(unsigned int *)((img.addr + (y * img.line_len) + (x * img.bpp / 8))));
	// res  = (*(unsigned int *)((img.addr + (y * img.line_len) + (x * img.bpp / 8))));
	// if (res >=  100)
	// {
	// 	return res;
	// 	// printf("res %d\n", res);
	// }
	
	return 0;
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
