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
			ptr = var->img->data_img + (((int)(y - MAP_sz / 4) * var->img->size_line) + (i * (var->img->bits_per_pixel / 8)));
			*(int *)ptr = color;
		}
		y++;
	}
}

void	my_put_pixel(t_img *img, int y, int x, int color)
{
	char	*ptr;
	
	ptr = img->data_img + ((y * img->size_line) + (x * (img->bits_per_pixel / 8)));
	*(int *)ptr = color;
}

void draw_dir(t_var *var, t_point cell, int color)
{

	int x0;
	int y0;
	int dx;
	int dy;
    int sx, sy, err, e2;

	int	count = 0; 
    y0 = 200;
    x0 = 200;

	cell.y = y0 + (int)((cell.y - var->player->pos_y) * (MAP_sz / GAME_sz));
	cell.x = x0 + (int)((cell.x - var->player->pos_x) * (MAP_sz / GAME_sz));

    dx = abs((int)cell.x - x0);
    dy = abs((int)cell.y - y0);

    sx = (x0 < (int)cell.x) ? 1 : -1;
    sy = (y0 < (int)cell.y) ? 1 : -1;

    err = dx - dy;
    while (1)
    {
        if (y0 > 0 && x0 > 0 && y0 < 400 && x0 < 400)
			my_put_pixel(var->img, y0, x0, color);
        // if ((x0 == (int)cell.x && y0 == (int)cell.y) || (count > (3 * MAP_sz)))
		if ((x0 == (int)cell.x && y0 == (int)cell.y))
            break;

        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
		count++;
    }
}

// void clear_image(t_var *var)
// {
//     int i;
//     int total_pixels = (int)((MAP_sz * var->map->width) * (MAP_sz * var->map->height));

// 	printf("width %f\n", var->width);
// 	printf("height %f\n", var->height);
//     for (i = 0; i < total_pixels; i++)
//         *(int *)(var->img->data_img + i * (var->img->bits_per_pixel / 8)) = 0xFFFF00; // Remplir avec une couleur transparente
// }

void	draw_map(t_img *img, int color, int i, int y)
{
	int save_i;
	int save_y;
	char *ptr;

	save_i = i;
	save_y = y;
	while (y < save_y + MAP_sz)
	{
		i = save_i;
		while (i < save_i + MAP_sz) /*largeur map*/
		{
			ptr = img->data_img + ((y * img->size_line) + (i * (img->bits_per_pixel / 8)));
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
				draw_map(var->img, 0x654321, x * MAP_sz, y * MAP_sz);
			}	
		}
		else if (y < 10 && y > 0)
		{
			while (x < 10)
			{
				if (x == 0 || x == 9)
					draw_map(var->img, 0x654321, x * MAP_sz, y * MAP_sz);
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

void	draw_minimap_cell(t_var *var, int cell_x, int cell_y, float scale)
{
	int		color;
	float	rel_x;
	float	rel_y;
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
	int		dx;
	int		dy;
	float	scale;

	px = (int)(var->player->pos_x / GAME_sz);
	py = (int)(var->player->pos_y / GAME_sz);
	scale = (float)MAP_sz / (float)GAME_sz;
	dy = -5;
	while (dy <= 5)
	{
		dx = -5;
		while (dx <= 5)
		{
			draw_minimap_cell(var, px + dx, py + dy, scale);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_var *var)
{
	top_minimap(var);
	// map_border(var);
	draw_map(var->img, 0x000000, 4.5 * MAP_sz, 4.5 * MAP_sz);
}

void	make_minimap(t_var *var)
{
	var->img = init_img();
	var->img->img = mlx_new_image(var->mlx, 10 * MAP_sz, 10 * MAP_sz);
	var->img->data_img = mlx_get_data_addr(var->img->img, &var->img->bits_per_pixel, &var->img->size_line, &var->img->endian);
	draw_minimap(var);
}
