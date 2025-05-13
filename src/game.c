#include "cub3D.h"

void	draw_game(t_img *img_g, int height, int width)
{
	int x;
	int	i;

	i = 0;
	while (i < height)
	{
		x = 0;
		while (x < width)
		{
			if (i < height / 2)
				my_put_pixel(img_g, i, x, 0xFFFFFF);
			else
				my_put_pixel(img_g, i, x, 0xFF0000);
			x++;
		}
		i++;
	}
}

// void	draw_game(t_img *img_g, int color, int i, int width)
// {
// 	int x;

// 	x = 0;
// 	while (x < width)
// 	{
// 		my_put_pixel(img_g, i, x, color);
// 		x++;
// 	}
// }

// void	make_game(t_var *var)
// {
// 	int	height;
// 	int	width;
// 	int i;

// 	height = 1200;
// 	width = 1900;
// 	var->img_g = init_img();
// 	var->img_g->img = mlx_new_image(var->mlx, width, height);
// 	var->img_g->data_img = mlx_get_data_addr(var->img_g->img, &var->img_g->bits_per_pixel, &var->img_g->size_line, &var->img_g->endian);
// 	i = 0;
// 	while (i < height)
// 	{
// 		if (i < height / 2)
// 			draw_game(var->img_g, 0xFFFFFF, i, width);
// 		else
// 			draw_game(var->img_g, 0xFF0000, i, width);
// 		i++;
// 	}
// 	printf("i = %d\n", i);
// }

void	draw_wall(t_var *var, int wall, int i)
{
	int y;
	int	y_end;
	int	j;

	y = (1200 - wall) / 2 ;
	y_end = y + wall;
	printf("y = %d\n", y);
	printf("wall = %d\n", wall);
	printf("i = %d\n", i);

	while (y < y_end)
	{
		if (y >= 0 && y < 1200) 
		{
			j = 0;
			while (j < 64)
			{
				my_put_pixel(var->img_g, y + j, i, 125);
				j++;
			}
			y++;
		}
	}

}


void	wall_height(t_var *var, int dist, int i)
{
	int	height_w;

	(void) dist;

printf("dist = %d\n", dist);
	height_w = 1200 / dist;
	// printf("dist = %d\n", height_w);

	// printf("x = %d", new_x);
	// printf("y = %d", new_y);
	draw_wall(var, height_w, i);
	
	/*fenetre / calcul rayon*/
	// Pour chaque rayon, tu dessines une ligne verticale de pixels, 
	// dont la hauteur est proportionnelle à la distance du mur, et la couleur peut dépendre de 
	// l'orientation du rayon (selon l'angle de vue du joueur).
}

void	make_game(t_var *var)
{
	int	height;
	int	width;

	height = 1200;
	width = 1900;
	var->img_g = init_img();
	var->img_g->img = mlx_new_image(var->mlx, width, height);
	var->img_g->data_img = mlx_get_data_addr(var->img_g->img, &var->img_g->bits_per_pixel, &var->img_g->size_line, &var->img_g->endian);
	draw_game(var->img_g, height, width);
}