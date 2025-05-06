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

void	find_wall_ray(t_var *var, int type)
{
	int new_x;
	int new_y;
	int ya;
	int xa;
	int num_rays = 50;
	float ray_step = var->player->fov / num_rays;
	float ray_angle;
	int i = 0;

	while (i++ < num_rays)
	{
		ray_angle = var->player->dir - (var->player->fov / 2) + i * ray_step;
		printf ("%f\n", ray_angle);
		xa = cos(ray_angle) * type;
		ya = sin(ray_angle) * type;
		new_x = var->player->map_x;
		new_y = var->player->map_y;
		// if (ya < 0)
		// 	new_y = ((int)(var->player->map_y / type) * type) - 1;
		// else if (ya > 0)
		// 	new_y = ((int)(var->player->map_y / type) * type) + type;
		// new_x = var->player->map_x + ((var->player->map_y - new_y) / tan(ray_angle));
		while (var->map->tab_map[(new_x / type)] != 0
			&& var->map->tab_map[(new_x / type)][(new_y / type)] != 0
			&& var->map->tab_map[(new_x / type)][(new_y / type)] != '1')
		{
			new_x = new_x + xa;
			new_y = new_y + ya;
		}
		if (var->map->tab_map[(int)(new_x / type)][(int)(new_y / type)] == '1')
			draw_dir(var, new_x, new_y, 0xFFFFFF);
	}
}

void	my_put_pixel(t_img *img, int y, int i, int color)
{
	char	*ptr;
	
	ptr = img->data_img + ((y * img->size_line) + (i * (img->bits_per_pixel / 8)));
	*(int *)ptr = color;
}

void	draw_dir(t_var *var, int x1, int y1, int color)
{
	int x0;
	int y0;
    int dx;
    int dy;

    int sx = (var->player->map_x < x1) ? 1 : -1;
    int sy = (var->player->map_y < y1) ? 1 : -1;
    int err;
    int e2;

	x0 = var->player->map_x;
	y0 = var->player->map_y;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
    while (1)
    {
       my_put_pixel(var->img, x0, y0, color);
 		if (x0 == x1 && y0 == y1)
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
