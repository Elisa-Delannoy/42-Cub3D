#include "cub3D.h"

void	draw_game(t_img *img_g, t_var *var)
{
	int x;
	int	i;

	i = 0;
	while (i < var->height)
	{
		x = 0;
		while (x < var->width)
		{
			if (i < var->height / 2)
				my_put_pixel(img_g, i, x, rgb_to_int(var->map->f));
			else
				my_put_pixel(img_g, i, x, rgb_to_int(var->map->c));
			x++;
		}
		i++;
	}
}

void	draw_wall(t_var *var, float wall, int i)
{
	float	y;
	float	y_end;

	y = (var->height - wall) / 2.0f ;
	y_end = y + wall;
	while (y < y_end)
	{
		if (var->cast->wall_dir == 'N')
			my_put_pixel(var->img_g, y, i, 0x00FF00);
		else if (var->cast->wall_dir == 'S')
			my_put_pixel(var->img_g, y, i, 0xFF0000);
		else if (var->cast->wall_dir == 'E')
			my_put_pixel(var->img_g, y, i, 0xFFFF00);
		else if (var->cast->wall_dir == 'W')
			my_put_pixel(var->img_g, y, i, 0xFFFFFF);
		y++;
	}
}



void	wall_height(t_var *var, float dist, int i)
{
	float	height_w;
	float	correc_dist;

	correc_dist = dist * cos(var->cast->ray - var->player->dir);
	if (correc_dist < 0.0001f)
		correc_dist = 0.0001f;
	height_w = (GAME_sz * var->height) / correc_dist;
	if (height_w > var->height)
		height_w = var->height;
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
	var->img_g = init_img();
	var->img_g->img = mlx_new_image(var->mlx, (int)var->width, (int)var->height);
	var->img_g->data_img = mlx_get_data_addr(var->img_g->img, &var->img_g->bits_per_pixel, &var->img_g->size_line, &var->img_g->endian);
	draw_game(var->img_g, var);
}
