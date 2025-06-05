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

void	draw_one_wall_pixel(t_var *var, t_cast *cast, int i, int y)
{
	int	color;

	color = *((int *)(cast->texture.data_img + (cast->text_pos_y 
	* cast->texture.line_len) + (cast->text_pos_x * cast->texture.bpp / 8)));
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
	step = (double)cast->texture.height / (y_end - y);
	cast->double_text_pos_y = 0;
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
	draw_game(var->img_g, var);
}
