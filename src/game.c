#include "cub3D.h"

void	draw_game(t_img *img_g, int color, int i, int width)
{
	int x;

	x = 0;
	while (x < width)
	{
		my_put_pixel(img_g, i, x, color);
		x++;
	}
}

void	make_game(t_var *var)
{
	int	height;
	int	width;
	int i;

	height = 1200;
	width = 1900;
	var->img_g = init_img();
	var->img_g->img = mlx_new_image(var->mlx, width, height);
	var->img_g->data_img = mlx_get_data_addr(var->img_g->img, &var->img_g->bits_per_pixel, &var->img_g->size_line, &var->img_g->endian);
	i = 0;
	while (i < height)
	{
		if (i < height / 2)
			draw_game(var->img_g, 0xFFFFFF, i, width);
		else
			draw_game(var->img_g, 0xFF0000, i, width);
		i++;
	}
	printf("i = %d\n", i);
}