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

int check_raycasting(float new_y, float new_x, int type, t_var *var)
{
	if (var->map->tab_map[((int)new_y / type)] != 0
		&& var->map->tab_map[((int)new_y / type)][((int)new_x / type)] != 0
		&& var->map->tab_map[((int)new_y / type)][((int)new_x / type)] == '1')
		return (0);
	else
		return (1);
	return (1);
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
	float num_rays = 100;
	float dstv;
	float dsth;
	float ray_step = var->player->fov / num_rays;
	float ray_angle;
	float i = 0;
	// if (fabs(data.v_hit.x - data.start.x) < fabs(data.h_hit.x - data.start.x))
	// while (i++ < num_rays)
	// {
		ray_angle = (var->player->dir - (var->player->fov / 2) + (i * ray_step));
		printf("\nJoueur: %f %f\n", var->player->map_x, var->player->map_y);
		printf("\n\n\n%f\n", ray_angle);
		if (sin(ray_angle) < 0)
		{
			yah = type;
			new_yh = (floor(var->player->map_y / (float)type) * (float)type) + type;
		}
		else
		{
			yah = -type;
			new_yh = (floor(var->player->map_y / (float)type) * (float)type) - 1;
		}
		new_xh = var->player->map_x + ((var->player->map_y - new_yh) / tan(ray_angle));
		xah = (float)type / tan(ray_angle);
		if ((xah > 0 && cos(ray_angle) < 0) || (xah < 0 && cos(ray_angle) > 0))
			xah *= -1;
		printf("\nHITH: %f %f\n", new_xh, new_yh);
		while (new_xh < 660 && new_yh < 280)
		{
			new_xh = new_xh + xah;
			new_yh = new_yh + yah;
			if (check_raycasting(new_yh, new_xh, type, var) == 0)
				break ;
		}
		dsth = distance(new_xh, new_yh, var->player->map_x, var->player->map_y);
		printf("step XH : %f\nstep YH : %f\ndistance horizonale : %f\n", xah, yah, dsth);
		draw_dir(var, new_yh, new_xh, 0xFFFFFF);


		if (cos(ray_angle) > 0)
		{
			xav = type;
			new_xv = (round(var->player->map_x / (float)type) * (float)type) + type;
		}
		else
		{
			xav = -type;
			new_xv = (round(var->player->map_x / (float)type) * (float)type) - 1;
		}
		new_yv = fabs(var->player->map_y + ((var->player->map_x - new_xv) * tan(ray_angle)));
		yav = (float)type * tan(ray_angle);
		if ((yav > 0 && sin(ray_angle) > 0) || (yav < 0 && sin(ray_angle) < 0))
			yav *= -1;
		while (check_raycasting(new_yv, new_xv, type, var) == 0)
		{
			new_xv = new_xv + xav;
			new_yv = new_yv + yav;
			if (new_xv > 660 || new_yv > 280)
				break ;
		}
		printf("\nHITV: %f %f\n", new_xv, new_yv);
		dstv = distance(new_xv, new_yv, var->player->map_x, var->player->map_y);
		printf("\nstep XV : %f\nstep YV : %f\ndistance verticale : %f\n", xav, yav, dstv);
		
		draw_dir(var, new_yv, new_xv, 0xFFFFFF);
	// }
	// exit(0);
}

void	my_put_pixel(t_img *img, int y, int x, int color)
{
	char	*ptr;
	
	ptr = img->data_img + ((y * img->size_line) + (x * (img->bits_per_pixel / 8)));
	*(int *)ptr = color;
}

void	draw_dir(t_var *var, int y1, int x1, int color)
{
	int x0;
	int y0;
    int dx;
    int dy;

    int sy = (var->player->map_y < y1) ? 1 : -1;
    int sx = (var->player->map_x < x1) ? 1 : -1;
    int err;
    int e2;

	y0 = var->player->map_y;
	x0 = var->player->map_x;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
    while (1)
    {
       my_put_pixel(var->img, y0, x0, color);
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
