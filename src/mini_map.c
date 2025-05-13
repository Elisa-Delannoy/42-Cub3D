#include "cub3D.h"

void	draw_player(t_var *var, int color, int y, int i)
{
	int save_i;
	int save_y;
	char *ptr;
	
	save_i = i;
	save_y = y;
	while (y < save_y + 10)
	{
		i = save_i;
		while (i++ < save_i + 10)
		{
			ptr = var->img->data_img + ((y * var->img->size_line) + (i * (var->img->bits_per_pixel / 8)));
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

void	draw_dir(t_var *var, t_point cell, int color)
{
	int x0;
	int y0;
    int dx;
    int dy;

    int sy = (var->player->map_y < (int)cell.y) ? 1 : -1;
    int sx = (var->player->map_x < (int)cell.x) ? 1 : -1;
    int err;
    int e2;

	y0 = var->player->map_y;
	x0 = var->player->map_x;
	dx = abs((int)cell.x - x0);
	dy = abs((int)cell.y - y0);
	err = dx - dy;
    while (1)
    {
       my_put_pixel(var->img, y0, x0, color);
 		if (x0 == (int)cell.x && y0 == (int)cell.y)
            break;
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
    }
}

void	draw_map(t_img *img, int color, int i, int y)
{
	int save_i;
	int save_y;
	char *ptr;

	save_i = i;
	save_y = y;
	while (y < save_y + 20)
	{
		i = save_i;
		while (i++ < save_i + 20) /*largeur map*/
		{
			ptr = img->data_img + ((y * img->size_line) + (i * (img->bits_per_pixel / 8)));
			*(int *)ptr = color;
		}
		y++;
	}
}

void	make_minimap(t_var *var)
{
	int i;
	int y;

	y = 0;
	var->img = init_img();
	// printf("%d\n, ")
	var->img->img = mlx_new_image(var->mlx, var->map->width * 20, var->map->height * 20);
	var->img->data_img = mlx_get_data_addr(var->img->img, &var->img->bits_per_pixel, &var->img->size_line, &var->img->endian);
	while (var->map->tab_map[y])
	{
		i = 0;
		while (var->map->tab_map[y][i])
		{
			if (var->map->tab_map[y][i] == '1')
				draw_map(var->img, 255, (i * 20), (y * 20));
			else if (var->map->tab_map[y][i] == '0')
				draw_map(var->img, 125, (i * 20), (y * 20));
			else if (var->map->tab_map[y][i] != ' ')
				draw_map(var->img, 125, (i * 20), (y * 20));
			i++;
		}
		y++;
	}
}
