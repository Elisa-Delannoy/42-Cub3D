#include "cub3D.h"

void draw_dir(t_var *var, t_point cell, int color, int i)
{
	int error;
	int	error_x2;
	int	count;
	double	coeff;
	
	var->minimap->x0 = MAP_sz * 5;
	var->minimap->y0 = MAP_sz * 5;
	count = 0;
	cell.y = (double)var->minimap->y0 + ((cell.y - var->player->pos_y) * (MAP_sz));
	cell.x = (double)var->minimap->x0 + ((cell.x - var->player->pos_x) * (MAP_sz));
	var->minimap->dist_x = abs((int)cell.x - var->minimap->x0);
	var->minimap->dist_y = abs((int)cell.y - var->minimap->y0);
		
	if (var->minimap->x0 < (int)cell.x)
		var->minimap->step_x = 1;
	else
		var->minimap->step_x = -1;
	if (var->minimap->y0 < (int)cell.y)
		var->minimap->step_y = 1;
	else
		var->minimap->step_y = -1;
	error = var->minimap->dist_x - var->minimap->dist_y;

	if (i < var->width / 3)
		color = modify_color(color, (double)i / (var->width / 3));
	if ( i >  2 * var->width / 3)
		color = modify_color(color, 1.f - (double)(i - 2 * (var->width / 3)) / (var->width / 3));
	while (1)
	{

		coeff = expf(-(double)count / (5 * MAP_sz) * 0.045);
		color = modify_color(color, coeff);
		if (var->minimap->y0 > 0 && var->minimap->x0 > 0 && var->minimap->y0 < MAP_sz * 10 - 1 && var->minimap->x0 < MAP_sz * 10 - 1)
			my_put_pixel(var->img, var->minimap->y0, var->minimap->x0, color);
		if ((var->minimap->x0 == (int)cell.x && var->minimap->y0 == (int)cell.y))
			break;
		error_x2 = 2 * error;
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
		count++;
    }
}

void	draw_mini_wall(t_var *var, int start_x, int start_y, t_img img)
{
	int x = 0;
	int y = 0;
	int color;
	int scale = 4;

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
				*(int *)(var->img->data_img + (start_y + y) * var->img->width + (start_x + x) * (var->img->height / 8)) = color;
			x++;
		}
		y++;
	}
}

void	map_border(t_var *var)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < MAP_sz * 10)
		my_put_pixel(var->img, y, x++, 0xFFFFFF);
	x--;
	while (y < MAP_sz * 10)
		my_put_pixel(var->img, y++, x, 0xFFFFFF);
	y--;
	while (x > 0)
		my_put_pixel(var->img, y, x--, 0xFFFFFF);
	while (y > 0)
		my_put_pixel(var->img, y--, x, 0xFFFFFF);
}

void	draw_minimap_pixel(t_var *var, int mini_x, int mini_y, int color)
{
	int i;
	int j;
	int px;
	int py;
	
	i = -1;
	while (++i < MAP_sz)
	{
		j = -1;
		while (++j < MAP_sz)
		{
			px = mini_x + j;
			py = mini_y + i;
			if (px >= 0 && py >= 0 && px < MAP_sz * 10 && py < MAP_sz * 10)
				my_put_pixel(var->img, py, px, color);
		}
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

void	draw_minimap_cell(t_var *var, int cell_x, int cell_y, double scale)
{
	int color;

	if (cell_x < 0 || cell_y < 0 || cell_x >= var->map->width
		|| cell_y >= var->map->height)
		return ;
	var->minimap->rel_x = (cell_x * GAME_sz) - var->player->pos_x;
	var->minimap->rel_y = (cell_y * GAME_sz) - var->player->pos_y;
	var->minimap->mini_x = MAP_sz * 5 + (int)(var->minimap->rel_x * scale);
	var->minimap->mini_y = MAP_sz * 5  + (int)(var->minimap->rel_y * scale);
	color = 0x0;
	draw_minimap_pixel(var, var->minimap->mini_x,
		var->minimap->mini_y, color);
	check_minimap_texture(var, cell_x, cell_y);
	if (var->map->tab_map[cell_y][cell_x] == 'O')
	{
		color = 0x3a003d;
		draw_minimap_pixel(var, var->minimap->mini_x,
			var->minimap->mini_y, color);
	}
}

void	do_minimap(t_var *var)
{
	int		px;
	int		py;
	int		delta_x;
	int		delta_y;
	double	scale;

	px = (int)(var->player->pos_x);
	py = (int)(var->player->pos_y);
	scale = (double)MAP_sz;
	delta_y = -5;
	while (delta_y <= 5)
	{
		delta_x = -5;
		while (delta_x <= 5)
		{
			draw_minimap_cell(var, px + delta_x, py + delta_y, scale);
			delta_x++;
		}
		delta_y++;
	}
}


void	draw_minimap(t_var *var)
{
	if (var->img->data_img != NULL)
		mlx_destroy_image(var->mlx, var->img->img);
	make_minimap(var);
	do_minimap(var);
	map_border(var);
	draw_mini_wall(var, 4.5 * MAP_sz, 4.5 * MAP_sz, var->icon);
}

void	make_minimap(t_var *var)
{
	var->img = init_img();
	var->img->img = mlx_new_image(var->mlx, 10 * MAP_sz, 10 * MAP_sz);
	var->img->data_img = mlx_get_data_addr(var->img->img, &var->img->height, &var->img->width, &var->img->endian);
	var->icon.img = mlx_xpm_file_to_image(var->mlx, "icon.xpm", &var->icon.width, &var->icon.height);
	var->icon.data_img = mlx_get_data_addr(var->icon.img, &var->icon.bpp, &var->icon.line_len, &var->icon.endian);
}
