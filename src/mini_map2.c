#include "cub3D.h"

int	init_value_dir(t_var *var, t_point *cell, int color, int i)
{
	int	error;

	var->minimap->x0 = MAP_sz * 5;
	var->minimap->y0 = MAP_sz * 5;
	((*cell).y) = (double)var->minimap->y0 + (((*cell).y - var->player->pos_y)
			* (MAP_sz));
	(*cell).x = (double)var->minimap->x0 + (((*cell).x - var->player->pos_x)
			* (MAP_sz));
	var->minimap->dist_x = abs((int)(*cell).x - var->minimap->x0);
	var->minimap->dist_y = abs((int)(*cell).y - var->minimap->y0);
	if (var->minimap->x0 < (int)(*cell).x)
		var->minimap->step_x = 1;
	else
		var->minimap->step_x = -1;
	if (var->minimap->y0 < (int)(*cell).y)
		var->minimap->step_y = 1;
	else
		var->minimap->step_y = -1;
	if (i < var->width / 3)
		color = shadow(color, (double)i / (var->width / 3));
	if (i > 2 * var->width / 3)
		color = shadow(color, 1.f - (double)(i - 2 * (var->width / 3))
				/ (var->width / 3));
	error = var->minimap->dist_x - var->minimap->dist_y;
	return (error);
}

int	find_dir(t_var *var, int error, int error_x2)
{
	if (error_x2 > -var->minimap->dist_y)
	{
		error -= var->minimap->dist_y;
		var->minimap->x0 += var->minimap->step_x;
	}
	if (error_x2 < var->minimap->dist_x)
	{
		error += var->minimap->dist_x;
		var->minimap->y0 += var->minimap->step_y;
	}
	return (error);
}

void	draw_dir(t_var *var, t_point cell, int color, int i)
{
	int		error;
	int		error_x2;
	int		count;
	double	coeff;

	count = 0;
	error = init_value_dir(var, &cell, color, i);
	while (1)
	{
		coeff = expf(-(double)count / (5 * MAP_sz) * 0.045);
		color = shadow(color, coeff);
		if (var->minimap->y0 > 0 && var->minimap->x0 > 0 && var->minimap->y0
			< MAP_sz * 10 - 1 && var->minimap->x0 < MAP_sz * 10 - 1)
			my_put_pixel(var->img, var->minimap->y0, var->minimap->x0, color);
		if ((var->minimap->x0 == (int)cell.x
				&& var->minimap->y0 == (int)cell.y))
			break ;
		error_x2 = 2 * error;
		error = find_dir(var, error, error_x2);
		count++;
	}
}

void	check_minimap_texture(t_var *var, int cell_x, int cell_y)
{
	t_img	texture;

	if (var->map->tab_map[cell_y][cell_x] == '1')
	{
		texture = var->no_t;
		draw_mini_wall(var, var->minimap->mini_x,
			var->minimap->mini_y, texture);
	}
	else if (var->map->tab_map[cell_y][cell_x] == 'D')
	{
		texture = var->door_t;
		draw_mini_wall(var, var->minimap->mini_x,
			var->minimap->mini_y, texture);
	}
	else if (var->map->tab_map[cell_y][cell_x] == 'X')
	{
		texture = var->exit_t;
		draw_mini_wall(var, var->minimap->mini_x,
			var->minimap->mini_y, texture);
	}
}

void	draw_mini_wall(t_var *var, int start_x, int start_y, t_img img)
{
	int	x;
	int	y;
	int	color;
	int	scale ;

	x = 0;
	y = 0;
	scale = 4;
	while (y < img.height / scale && start_y + y < MAP_sz * 10)
	{
		x = 0;
		while (x < img.width / scale && start_x + x < MAP_sz * 10)
		{
			int src_x = x * scale;
			int src_y = y * scale;

			color = *(int *)(img.data_img
			 + (src_y * img.line_len) + (src_x * (img.bpp / 8)));
			if ((color >> 24 & 0xFF) == 0)
				*(int *)(var->img->data_img + (start_y + y) * var->img->width
					+ (start_x + x) * (var->img->height / 8)) = color;
			x++;
		}
		y++;
	}
}


// void	draw_img_in_img(t_var *var, t_img image, int sx, int sy)
// {
// 	int		x;
// 	int		y;
// 	int		scl;

// 	y = -1;
// 	scl = 2;
// 	if (image.img == var->gameover.img || image.img == var->victory.img)
// 		scl = 4;
// 	while (++y + sy < var->height && y < image.height * scl)
// 	{
// 		x = -1;
// 		while (++x + sx < var->width && x < image.width * scl)
// 		{
// 			var->light->colo = *(int *)(image.data_img
// 					+ (y / scl * image.line_len) + (x / scl * (image.bpp / 8)));
// 			if ((var->light->colo >> 24 & 0xFF) == 0)
// 			{
// 				var->light->coeff = find_coeff(var, image);
// 				var->light->colo = shadow(var->light->colo, var->light->coeff);
// 				*(int *)(var->img_g->data_img + (sx + x) * (var->img_g->height
// 							/ 8) + (sy + y) * var->img_g->width)
// 					= var->light->colo;
// 			}
// 		}
// 	}
// }