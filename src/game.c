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
				my_put_pixel(img_g, i, x, var->map->color_f);
			else
				my_put_pixel(img_g, i, x, var->map->color_c);
			x++;
		}
		i++;
	}
}

void	put_texture(t_var *var, int y, int i, double wall, int texture_x)
{
	int color;
	int pixel;
	const int	*ptr;

	pixel = (int)(y / (wall / var->no_t.height));
	
	ptr = (int *)var->no_t.data_img;
	// ptr = var->no_t.data_img + ((pixel * var->no_t.width) + (i * (var->no_t.height / 8)));
	color = ptr[pixel * var->no_t.height + texture_x];
	my_put_pixel(var->img_g, y, i, color);
}

void	draw_wall(t_var *var, double wall, int i, int w_coordinates, int texture_x)
{
	double	y;
	double	y_end;
	double	step;
	double	textpos;
	int		texty;
	int		color;

	y = -wall / 2.0f + var->height / 2.0f;
	y_end = wall / 2.0f + var->height / 2.0f;
	if (y < 0)
		y = 0;
	if (y_end >= var->height)
		y_end = var->height - 1;
	// printf("hauteur texture %d\n", var->no_t.height);
	// printf("hauteur mur %f\n", wall);
	// printf("hauteur mur %f\n", y_end - y);
	step = (double)var->no_t.height / (y_end - y);
	// printf("step %f\n", step);
	textpos = 0;
	// y_end = y + wall;
	while (y < y_end)
	{
		if (textpos < 0)
			textpos = 0;
		if (textpos >= var->no_t.height)
			textpos = 0;
		texty = (int)textpos;
		// texty = (int)textpos;
		// printf("textpos %f\n", textpos);
		color = *((int *)(var->no_t.data_img + (texty * var->no_t.line_len)
		+ (texture_x * var->no_t.bpp / 8)));
		
		// my_put_pixel(var->img_g, y, i, 0x00FF00);
		// if (var->cast->wall_dir == NORTH)
		// 	my_put_pixel(var->img_g, y, i, 0x00FF00);
		if (w_coordinates == NORTH)
			my_put_pixel(var->img_g, (int)y, i, color);	
		else if (w_coordinates == SOUTH)
			my_put_pixel(var->img_g, y, i, 0x00FF00);
		else if (w_coordinates == EAST)
			my_put_pixel(var->img_g, y, i, 0xF2EDF1);
		else if (w_coordinates == WEST)
			my_put_pixel(var->img_g, y, i, 0xDAA935);
		// printf("y = %f, texty = %d\n", y, texty);
		textpos += step;
		y++;
		}
		
		// else if (var->cast->wall_dir == SOUTH)
		// 	my_put_pixel(var->img_g, y, i, 0xFF0000);
		// else if (var->cast->wall_dir == EAST)
		// 	my_put_pixel(var->img_g, y, i, 0xFFFF00);
		// else if (var->cast->wall_dir == WEST)
		// 	my_put_pixel(var->img_g, y, i, 0xFFFFFF);
		

}



// void	wall_height(t_var *var, double dist, int i)
// {
// 	double	height_w;
// 	double	correc_dist;

// 	correc_dist = dist * cos(var->cast->ray - var->player->dir);
// 	if (correc_dist < 0.0001f)
// 		correc_dist = 0.0001f;
// 	height_w = (GAME_sz * var->height) / correc_dist;
// 	if (height_w > var->height)
// 		height_w = var->height;
// 	if (height_w < 0)
// 		height_w = 0;
// 	draw_wall(var, height_w, i);
// }

void	make_game(t_var *var)
{
	var->img_g = init_img();
	var->img_g->img = mlx_new_image(var->mlx, (int)var->width, (int)var->height);
	var->img_g->data_img = mlx_get_data_addr(var->img_g->img, &var->img_g->height, &var->img_g->width, &var->img_g->endian);
	draw_game(var->img_g, var);
}
