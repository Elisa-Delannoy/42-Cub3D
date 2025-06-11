#include "cub3D.h"

int	check_in_map(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= map->width)
		return (2);
	return (1);
}

void	my_put_pixel(t_img *img, int y, int x, int color)
{
	char	*ptr;
	
	ptr = img->data_img + ((y * img->width) + (x * (img->height / 8)));
	*(int *)ptr = color;
}
