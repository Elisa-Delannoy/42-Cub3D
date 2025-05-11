#include "cub3D.h"

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

int	distance(float x1, float y1, float x0, float y0)
{
	return (sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0))));
}

void	find_wall_ray(t_var *var, int type)
{
	float new_xv;
	float new_yv;
	float new_xh;
	float new_yh;
	float yav;
	float xav;
	float yah;
	float xah;
	float num_rays = 10000;
	float dstv;
	float dsth;
	float ray_step = var->player->fov / num_rays;
	float ray_angle;
	float i = 50;

	// while (i++ < num_rays)
	// {
		ray_angle = (var->player->dir - (var->player->fov / 2) + i * ray_step);
		// ray_angle = (PI / 2) + 0.1;
		printf("\n\n\n%f\n", ray_angle);
		if (cos(ray_angle) < 0)
		{
			yah = type;
			new_yh = ((int)(var->player->map_y / type) * type) + type;
		}
		else
		{
			yah = -type;
			new_yh = ((int)(var->player->map_y / type) * type) - 1;
		}
		new_xh = var->player->map_x + ((var->player->map_y - new_yh) / tan(ray_angle));
		xah = type / tan(ray_angle);
		while (var->map->tab_map[((int)new_xh / type)] != 0
			&& var->map->tab_map[((int)new_xh / type)][((int)new_yh / type)] != 0
			&& var->map->tab_map[((int)new_xh / type)][((int)new_yh / type)] != '1')
		{
			new_xh = new_xh + xah;
			new_yh = new_yh + yah;
		}
		dsth = distance(new_xh, new_yh, var->player->map_x, var->player->map_y);
		printf("step XH : %f\nstep YH : %f\ndistance Verticale : %f\n", xah, yah, dsth);

	
		if (sin(ray_angle) > 0)
		{
			xav = type;
			new_xv = ((int)(var->player->map_x / type) * type) + type;
		}
		else
		{
			xav = -type;
			new_xv = ((int)(var->player->map_x / type) * type) - 1;
		}
		new_yv = var->player->map_y + ((var->player->map_x - new_xv) * tan(ray_angle));
		yav = type / tan(ray_angle);
		while (var->map->tab_map[((int)new_xv / type)] != 0
			&& var->map->tab_map[((int)new_xv / type)][((int)new_yv / type)] != 0
			&& var->map->tab_map[((int)new_xv / type)][((int)new_yv / type)] != '1')
		{
			new_xv = new_xv + xav;
			new_yv = new_yv + yav;
		}
		dstv = distance(new_xv, new_yv, var->player->map_x, var->player->map_y);
		printf("\nstep XV : %f\nstep YV : %f\ndistance Horizontale : %f\n", xav, yav, dstv);
		// draw_dir(var, new_xh, new_yh, 0xFFFFFF);
		draw_dir(var, new_xv, new_yv, 0xFFFFFF);
	// }
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
