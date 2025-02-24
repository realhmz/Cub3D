#include "cub.h"

void	line_init(t_line *line, int x1, int y1, int y2)
{
	line->dx = x1 - x1;
	line->dy = y2 - y1;
	if (abs((int)line->dx) > abs((int)line->dy))
		line->step = abs((int)line->dx);
	else
		line->step = abs((int)line->dy);
	line->inc_x = line->dx / line->step;
	line->inc_y = line->dy / line->step;
	line->curr_x = x1;
	line->curr_y = y1;
}

int	draw_line_simple(int x1, int y1, int y2, t_game *game)
{
	t_line	line;
	int		i;
	int		color;

	line_init(&line, x1, y1, y2);
	i = 0;
	while (i <= line.step)
	{
		color = calc_darkness(i * 1.5, game->color);
		put_pixel_img(game->back, (int)line.curr_x, (int)line.curr_y, color);
		line.curr_x += line.inc_x;
		line.curr_y += line.inc_y;
		i++;
	}
	return (500);

}

int	calc_darkness(double dst, int color)
{
	int	r;
	int	g;
	int	b;

	r = color / 256 / 256;
	g = (color / 256) % 256;
	b = color % 256;
	r = r - (dst / 4);
	g = g - (dst / 4);
	b = b - (dst / 4);
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r * 256 * 256 + g * 256 + b);
}