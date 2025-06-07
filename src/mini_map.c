#include "cub3D.h"

void	draw_player(t_var *var, int color, int y, int i)
{
	int save_i;
	int save_y;
	char *ptr;
	
	save_i = i - MAP_sz / 4;
	save_y = y;
	while (y < save_y + MAP_sz / 2)
	{
		i = save_i;
		while (i++ < save_i + MAP_sz / 2)
		{
			ptr = var->img->data_img + (((int)(y - MAP_sz / 4) * var->img->width) + (i * (var->img->height / 8)));
			*(int *)ptr = color;
		}
		y++;
	}
}

void	my_put_pixel(t_img *img, int y, int x, int color)
{
	char	*ptr;
	
	ptr = img->data_img + ((y * img->width) + (x * (img->height / 8)));
	*(int *)ptr = color;
}

void draw_dir(t_var *var, t_point cell, int color, int i)
{
	int error;
	int	error_x2;
	int	count;
	// int	ratio = var->map->height / (10 * MAP_sz / 3);
	double	coeff;
	int	dist;
	
	var->minimap->x0 = 200;
	var->minimap->y0 = 200;
	count = 0;
	cell.y = (double)var->minimap->y0 + ((cell.y - var->player->pos_y) * (MAP_sz));
	cell.x = (double)var->minimap->x0 + ((cell.x - var->player->pos_x) * (MAP_sz));
	var->minimap->dist_x = abs((int)cell.x - var->minimap->x0);
	var->minimap->dist_y = abs((int)cell.y - var->minimap->y0);
	dist = sqrt(var->minimap->dist_x * var->minimap->dist_x + var->minimap->dist_y *var->minimap->dist_y);
		
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
		color = modify_color (color, (double)i / (var->width / 3));
	if ( i >  2 * var->width / 3)
		color = modify_color (color, 1.f - (double)(i - 2 * (var->width / 3)) / (var->width / 3));
	while (1)
	{
		// coeff = expf(-(double)(count + 1) / dist * 0.05f);
		// coeff = expf(-cast->dist * 0.2f);
		// printf("%f\n", coeff);
		// if (count > 5 * MAP_sz)
		// 	coeff = 0.2;
		// else if (count > 4 * MAP_sz)
		// 	coeff = 0.4;
		// else if (count > 3 * MAP_sz)
		// 	coeff = 0.6;
		// else if (count > 2 * MAP_sz)
		// 	coeff = 0.8;
		// else
		// 	coeff = 1;
		
		coeff = expf(-(double)count / (7 * MAP_sz) * 0.05);
		if (count > 7 * MAP_sz)
			coeff = 0;
		
		// int ratio =  / (var->width / 3);
		// if ((var->minimap->y0 < (10 * MAP_sz / 3 + 10 * MAP_sz / 6)  && i < ((y + var->height / 6) / ratio)) || ((var->width - i) < ((y + var->height / 6) / ratio) && i > (2 * var->width / 6 - var->height / 3)))
		// coeff = 0.1;

		color = modify_color (color, coeff);

		if (count > 19 && var->minimap->y0 > MAP_sz && var->minimap->x0 > MAP_sz - 1 && var->minimap->y0 < 400 - MAP_sz && var->minimap->x0 < 400 - MAP_sz)
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

void	draw_map(t_img *img, int color, int i, int y)
{
	int save_i;
	int save_y;
	char *ptr;

	save_i = i;
	save_y = y;
	while (y < save_y +MAP_sz)
	{
		i = save_i;
		while (i < save_i + MAP_sz) /*largeur map*/
		{
			ptr = img->data_img + ((y * img->width) + (i * (img->height / 8)));
			*(int *)ptr = color;
			i++;
		}
		y++;
	}
}

void	map_border(t_var *var)
{
	int x;
	int y;

	y = 0;
	while (y < 10)
	{
		x = -1;
		if (y == 0 || y == 9)
		{
			while (++x < 10)
			{
				draw_map(var->img, 0x39201a, x * MAP_sz, y * MAP_sz);
			}	
		}
		else if (y < 10 && y > 0)
		{
			while (x < 10)
			{
				if (x == 0 || x == 9)
					draw_map(var->img, 0x39201a, x * MAP_sz, y * MAP_sz);
				x++;
			}
		}
		y++;
	}
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
			if (px >= 0 && py >= 0 && px < 400 && py < 400)
				my_put_pixel(var->img, py, px, color);
		}
	}
}

void	draw_minimap_cell(t_var *var, int cell_x, int cell_y, double scale)
{
	int		color;
	double	rel_x;
	double	rel_y;
	int		mini_x;
	int		mini_y;

	if (cell_x < 0 || cell_y < 0 || cell_x >= var->map->width
		|| cell_y >= var->map->height)
		return ;
	color = (var->map->tab_map[cell_y][cell_x] == '1') ? 0x3a3c3d : 0x9e9c9a;
	rel_x = (cell_x * GAME_sz) - var->player->pos_x;
	rel_y = (cell_y * GAME_sz) - var->player->pos_y;
	mini_x = 200 + (int)(rel_x * scale);
	mini_y = 200 + (int)(rel_y * scale);
	draw_minimap_pixel(var, mini_x, mini_y, color);
}

void	top_minimap(t_var *var)
{
	int		px;
	int		py;
	int		delta_x;
	int		delta_y;
	double	scale;

	px = (int)(var->player->pos_x);
	py = (int)(var->player->pos_y );
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
	top_minimap(var);
	map_border(var);
	draw_map(var->img, 0x39201a, 4.5 * MAP_sz, 4.5 * MAP_sz);
}

void	make_minimap(t_var *var)
{
	var->img = init_img();
	var->img->img = mlx_new_image(var->mlx, 10 * MAP_sz, 10 * MAP_sz);
	var->img->data_img = mlx_get_data_addr(var->img->img, &var->img->height, &var->img->width, &var->img->endian);
}
