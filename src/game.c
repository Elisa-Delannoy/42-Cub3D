#include "cub3D.h"

// void	draw_game(t_img *img_g, t_var *var)
// {
// 	int x;
// 	int	i;
// 	double	coeff_f;
// 	double	coeff_c;
// 	double	ratio;

// 	ratio =  var->height / (var->width / 2);
// 	x = 0;
// 	while (x < var->width)
// 	{
// 		i = 0;
// 		// coeff_f = 1;
// 		while (i < var->height)
// 		{
// 			coeff_c = 1.f - (double)i / (double)((var->height - 1) / 2);
// 			if (coeff_c > 0.45)
// 				coeff_c = 0.45;
// 			coeff_f = ((double)(i - var->height / 2)) / ((var->height / 2) - 1) + 0.45f;
			


			
// 			if (i < var->height / 2)
// 			{
// 				if ((x < ((var->width / 2) -30 + (double)(i - var->height) * (-((var->width / 2) -30)) / (150 - var->height)))
// 				|| ((var->width - x) < ((i / ratio) - 100) && x > (var->width / 6 - var->height / 2)))
// 				coeff_c = 0.1;
// 				my_put_pixel(img_g, i, x, modify_color(var->map->color_c, coeff_c));
// 			}
// 			else
// 			{
// 				if ((x < ((var->width / 2) -30 + (double)(i - var->height) * (-((var->width / 2) -30)) / (150 - var->height)))
// 				|| ((var->width - x) < ((i / ratio) - 100) && x > (var->width / 6 - var->height / 2)))
// 					coeff_f = 0.1;
// 				my_put_pixel(img_g, i, x, modify_color(var->map->color_f, coeff_f));
// 			}
// 			i++;
// 		}
// 		x++;
// 	}
// }


void	draw_game(t_img *img_g, t_var *var)
{
	int x;
	int	i;
	double	coeff_f;
	double	coeff_c;
	double	ratio;

	ratio =  var->height / (var->width / 2);
	x = 0;

	int top = 150;                 // i où le faisceau s’arrête en haut
	int bottom = var->height - 1;  // i en bas (le bas de l’écran)

	int center = var->width / 2;

	// Bord gauche : de (bottom, center - 30) à (top, 0)
	int left_bottom = center - 30;
	int left_top = 0;

	// Bord droit : de (bottom, center + 100) à (top, var->width)
	int right_bottom = center + 100;
	int right_top = var->width;


	while (x < var->width)
	{
		i = 0;
		// coeff_f = 1;
		while (i < var->height)
		{
			coeff_c = 1.f - (double)i / (double)((var->height - 1) / 2);
			if (coeff_c > 0.45)
				coeff_c = 0.45;
			coeff_f = ((double)(i - var->height / 2)) / ((var->height / 2) - 1) + 0.45f;
			
			double x_left = left_bottom + (i - bottom) * (left_top - left_bottom) / (double)(top - bottom);
			double x_right = right_bottom + (i - bottom) * (right_top - right_bottom) / (double)(top - bottom);


			
			if (i < var->height / 2)
			{
				if ((i >= top && (x < x_left || x > x_right)))
					coeff_c = 0.1;
				my_put_pixel(img_g, i, x, modify_color(var->map->color_c, coeff_c));
			}
			else
			{
				if ((i >= top && (x < x_left || x > x_right)))
					coeff_f = 0.1;
				my_put_pixel(img_g, i, x, modify_color(var->map->color_f, coeff_f));
			}
			i++;
		}
		x++;
	}
}

void	draw_one_wall_pixel(t_var *var, t_cast *cast, int i, int y)
{
	int	color;
	double	coeff;
	double	ratio;

	color = *((int *)(cast->texture.data_img + (cast->text_pos_y 
	* cast->texture.line_len) + (cast->text_pos_x * cast->texture.bpp / 8)));
	ratio =  var->height / (var->width / 2);
	

	coeff = expf(-cast->dist * 0.2f);
	// if ((i < ((var->width / 2) -30 + (double)(y - var->height) * (-((var->width / 2) -30)) / (150 - var->height)))
	// 			|| ((var->width - i) < ((y / ratio) - 100) && i > (var->width / 6 - var->height / 2)))
	// 	coeff = 0.1;
	
	
	int top = 150;                 // i où le faisceau s’arrête en haut
	int bottom = var->height - 1;  // i en bas (le bas de l’écran)

	int center = var->width / 2;

	// Bord gauche : de (bottom, center - 30) à (top, 0)
	int left_bottom = center - 30;
	int left_top = 0;

	// Bord droit : de (bottom, center + 100) à (top, var->width)
	int right_bottom = center + 100;
	int right_top = var->width;

	double x_left = left_bottom + (y - bottom) * (left_top - left_bottom) / (double)(top - bottom);
	double x_right = right_bottom + (y - bottom) * (right_top - right_bottom) / (double)(top - bottom);

	if ((y >= top && (i < x_left || i > x_right)))
		coeff = 0.1;


	color = modify_color (color, coeff);
	if ((color >> 24 & 0xFF) == 0)
		my_put_pixel(var->img_g, (int)y, i, color);
	
}

void	draw_wall(t_var *var, t_cast *cast, int i)
{
	double	y;
	double	y_end;
	double	step;

	y = -cast->wall_h / 2.0f + var->height / 2.0f;
	y_end = cast->wall_h / 2.0f + var->height / 2.0f;
	if (y < 0)
		y = 0;
	if (y_end >= var->height)
		y_end = var->height - 1;
	step = (double)cast->texture.height / (cast->wall_h);
	cast->double_text_pos_y = (y - var->height / 2 + cast->wall_h / 2) * step;
	while (y < y_end)
	{
		if (cast->double_text_pos_y < 0)
			cast->double_text_pos_y = 0;
		if (cast->double_text_pos_y >= cast->texture.height)
			cast->double_text_pos_y = cast->texture.height - 1;
		cast->text_pos_y = (int)cast->double_text_pos_y;
		draw_one_wall_pixel(var, cast, i, y);
		cast->double_text_pos_y += step;
		y++;
	}
}

void	make_game(t_var *var)
{
	var->img_g = init_img();
	var->img_g->img = mlx_new_image(var->mlx, (int)var->width, (int)var->height);
	var->img_g->data_img = mlx_get_data_addr(var->img_g->img, &var->img_g->height, &var->img_g->width, &var->img_g->endian);
}
