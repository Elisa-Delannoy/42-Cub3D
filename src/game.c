#include "cub3D.h"

void	draw_game(t_img *img_g, t_var *var)
{
	int x;
	int	i;
	double	coeff_f;
	double	coeff_c;
	double	ratio;

	ratio =  var->height / (var->width / 3);
	x = 0;
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
			
			if (i < var->height / 2)
			{
				if ((x < (var->width / 3 + var->height / 6)  && x < ((i + var->height / 6) / ratio)) || ((var->width - x) < ((i + var->height / 6) / ratio) && x > (2 * var->width / 6 - var->height / 3)))
					coeff_c = 0.1;
				my_put_pixel(img_g, i, x, modify_color(var->map->color_c, coeff_c));
			}
			else
			{
				if ((x < (var->width / 3 + var->height / 6)  && x < ((i + var->height / 6) / ratio)) || ((var->width - x) < ((i + var->height / 6) / ratio) && x > (2 * var->width / 6 - var->height / 3)))
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
	ratio =  var->height / (var->width / 3);
	

	coeff = expf(-cast->dist * 0.2f);
	if ((i < (var->width / 3 + var->height / 6)  && i < ((y + var->height / 6) / ratio)) || ((var->width - i) < ((y + var->height / 6) / ratio) && i > (2 * var->width / 6 - var->height / 3)))
		coeff = 0.1;
	color = modify_color (color, coeff);
	if (cast->wall_dir == NORTH)
		my_put_pixel(var->img_g, (int)y, i, color);
	else if (cast->wall_dir == SOUTH)
		my_put_pixel(var->img_g, y, i, color);
	else if (cast->wall_dir == EAST)
		my_put_pixel(var->img_g, y, i, color);
	else if (cast->wall_dir == WEST)
		my_put_pixel(var->img_g, y, i, color);
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
