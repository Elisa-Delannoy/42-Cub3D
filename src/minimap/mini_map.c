#include "cub3D.h"

void	map_border(t_var *var)
{
	int	y;
	int	x;

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
	int	i;
	int	j;
	int	px;
	int	py;

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

void	draw_minimap_cell(t_var *var, int cell_x, int cell_y, double scale)
{
	int	color;

	if (cell_x < 0 || cell_y < 0 || cell_x >= var->map->width
		|| cell_y >= var->map->height)
		return ;
	var->minimap->rel_x = (cell_x * GAME_sz) - var->player->pos_x;
	var->minimap->rel_y = (cell_y * GAME_sz) - var->player->pos_y;
	var->minimap->mini_x = MAP_sz * 5 + (int)(var->minimap->rel_x * scale);
	var->minimap->mini_y = MAP_sz * 5 + (int)(var->minimap->rel_y * scale);
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
