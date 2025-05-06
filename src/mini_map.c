#include "../cub3D.h"

void	draw_player(t_var *var, int color, int i, int y)
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

// void	find_wall_ray(t_var *var)
// {
// 	double ray_x = var->player->y;
// 	double ray_y = var->player->x;
// 	double step_size = 0.01;

// 	while (var->map->tab_map[(int)ray_y][(int)ray_x] != '1')
// 	{
// 		ray_x += cos(radian(110)) * step_size;
// 		ray_y += sin(radian(110)) * step_size;
// 	}
// 	draw_dir(var, ((34 - ray_x) * 20), ((14 - ray_y) * 20), 0xFF0140);
// }

// void	draw_dir(t_var *var, int x1, int y1, int color)
// {
// 	int x0;
// 	int y0;
//     int dx;
//     int dy;
//     int sx = (var->player->x < x1) ? 1 : -1;
//     int sy = (var->player->y < y1) ? 1 : -1;
//     int err;
//     int e2;

// 	x0 = ((34 - var->player->y - 0.5) * 20);
// 	y0 = ((14 - var->player->x - 0.5) * 20);
// 	dx = abs(x1 - x0);
// 	dy = abs(y1 - y0);
// 	err = dx - dy;
//     while (1)
//     {
//        mlx_pixel_put(var->mlx, var->win, x0, y0, color);
//  		if (x0 == x1 && y0 == y1)
//             break;
//         e2 = 2 * err;
//         if (e2 > -dy) { err -= dy; x0 += sx; }
//         if (e2 < dx)  { err += dx; y0 += sy; }
//     }
// }

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
	var->img->img = mlx_new_image(var->mlx, 34*20, 14*20);
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
