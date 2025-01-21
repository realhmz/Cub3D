#include "cub.h"

int	calc_map_h(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}
int	max_width(char **map)
{
	int	i;
	int	j;
	int max;

	i = 0;
	j = 0;
	max = ft_strlen(map[0]);
	while (map && map[i])
	{
		j = ft_strlen(map[i]);
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

int	get_ceiling_color(int *rgb)
{
	int res;

	res = rgb[0] * 256 * 256;
	res += rgb[1] * 256;
	res += rgb[2];
	return (res);
}
int	get_pv(char pv)
{
	int	res;

	if (pv == 'N')
		res = 270;
	else if (pv == 'S')
		res = 90;
	else if (pv == 'W')
		res = 180;
	else if (pv == 'E')
		res = 0;
	return (res);
}