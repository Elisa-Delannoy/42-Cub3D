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
	cell.y = cell.y / var->map->g_to_m;
	cell.x = cell.x / var->map->g_to_m;

    y0 = var->player->pos_y / var->map->g_to_m;
    x0 = var->player->pos_x / var->map->g_to_m;

    dx = abs((int)cell.x - x0);
    dy = abs((int)cell.y - y0);

    sx = (x0 < (int)cell.x) ? 1 : -1;
    sy = (y0 < (int)cell.y) ? 1 : -1;

    err = dx - dy;
    while (1)
    {
        my_put_pixel(var->img, y0, x0, color);
        if ((x0 == (int)cell.x && y0 == (int)cell.y) || (count > (3 * MAP_sz)))
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

void	draw_minimap(t_var *var)
{
	int	i;
	int	y;

	y = 0;
	while (var->map->temp[y])
	{
		i = 0;
		while (var->map->temp[y][i])
		{
			if (var->map->temp[y][i] == '1')
				draw_map(var->img, 255, (i * MAP_sz), (y * MAP_sz));
			else if (var->map->temp[y][i] == '0' || var->map->temp[y][i] != '2')
				draw_map(var->img, 125, (i * MAP_sz), (y * MAP_sz));
			else if (var->map->temp[y][i] == '2')
				;
			i++;
		}
		y++;
	}
}

void	make_minimap(t_var *var)
{
	var->img = init_img();
	var->img->img = mlx_new_image(var->mlx, var->map->width * MAP_sz, var->map->height * MAP_sz);
	var->img->data_img = mlx_get_data_addr(var->img->img, &var->img->bits_per_pixel, &var->img->size_line, &var->img->endian);
	draw_minimap(var);
}
