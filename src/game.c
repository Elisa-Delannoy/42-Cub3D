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
				my_put_pixel(img_g, i, x, 0x000050);
			else
				my_put_pixel(img_g, i, x, 0x505050);
			x++;
		}
		i++;
	}
}

void	draw_wall(t_var *var, int wall, int i)
{
	int y;
	int	y_end;

	y = (1200 - wall) / 2 ;
	y_end = y + wall;
	printf("y = %d\n", y);
	
	printf("i = %d\n", i);

	while (y < y_end)
	{
		my_put_pixel(var->img_g, y, i, 0xFF0000);
		y++;
	}
}

void	wall_height(t_var *var, float dist, int i)
{
	float	height_w;
	float	correc_dist;

	(void) dist;
	// var->cast->ray = fmod(var->play->angle
				// - (var->player->fov / 2), 360.0)); - (double)var->play->dir, 360.0);
	// height_w =  fabs((64 * 1200) / (dist / 20 * 64) * cos(var->cast->ray)screen_width / 2) / tan(fov / 2););
	// height_w =  64 / dist;

	printf("var ray %f\n", var->cast->ray * 180 / PI);
	correc_dist = (float)dist * cos(var->cast->ray - var->player->dir);
	if (correc_dist < 0.0001f)
		correc_dist = 0.0001f;

	// height_w = ((64.0f / (correc_dist)) * ((1200.0f / 2.0f) / tan(var->player->fov / 2.0f)));
	height_w = (64.0f * 1200.0f) / correc_dist;
	if (height_w > 1200)
		height_w = 1200;
	if (height_w < 0)
		height_w = 0;
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