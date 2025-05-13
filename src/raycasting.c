#include "cub3D.h"

t_point	raycating_horizontal(t_var *var, t_cast *cast, float type)
{
	t_point cell;
	
	if (sin(cast->ray) < 0)
	{
		cast->step_y = type;
		cell.y = (floor(var->player->map_y / (float)type) * (float)type) + type;
	}
	else
	{
		cast->step_y = -type;
		cell.y = (floor(var->player->map_y / (float)type) * (float)type) - 1;
	}
	cell.x = var->player->map_x + ((var->player->map_y - cell.y) / tan(cast->ray));
	cast->step_x = (float)type / tan(cast->ray);
	if ((cast->step_x > 0 && cos(cast->ray) < 0) || (cast->step_x < 0 && cos(cast->ray) > 0))
		cast->step_x *= -1;
	while (1)
	{
		if (check_raycasting(cell.y, cell.x, type, var) == 0)
			break ;
		cell.x += cast->step_x;
		cell.y += cast->step_y;
	}
	return (cell);
}

t_point	raycating_vertical(t_var *var, t_cast *cast, float type)
{
	t_point cell;

	if (cos(cast->ray) > 0)
	{
		cast->step_x = type;
		cell.x = (round(var->player->map_x / (float)type) * (float)type) + type;
	}
	else
	{
		cast->step_x = -type;
		cell.x = (round(var->player->map_x / (float)type) * (float)type) - 1;
	}
	cell.y = fabs(var->player->map_y + ((var->player->map_x - cell.x) * tan(cast->ray)));
	cast->step_y = (float)type * tan(cast->ray);
	if ((cast->step_y > 0 && sin(cast->ray) > 0) || (cast->step_y < 0 && sin(cast->ray) < 0))
		cast->step_y *= -1;
	while (1)
	{
		if (check_raycasting(cell.y, cell.x, type, var) == 0)
			break ;
		cell.x += cast->step_x;
		cell.y += cast->step_y;
	}
	return(cell);
}

int	valid_point(t_var *var, t_point cell, int type)
{
	if ((cell.y > 0  && cell.x > 0)
		&& (cell.x < var->map->width * type
		&& cell.y < var->map->height * type))
		return (0);
	return (1);
}

void	raycasting(t_var *var, int type)
{
	int i;
	float	ray_step;

	ray_step = var->player->fov / 1900;
	i = 0;
	while (i++ < 1900)
	{
		var->cast->ray = (var->player->dir - (var->player->fov / 2) + (i * ray_step));
		var->cast->h = raycating_horizontal(var, var->cast, type);
		var->cast->v = raycating_vertical(var, var->cast, type);
		var->cast->disth = distance(var->cast->h, var->player->map_x, var->player->map_y);
		var->cast->distv = distance(var->cast->v, var->player->map_x, var->player->map_y);
		if (type == MAP && var->cast->disth < var->cast->distv
			&& valid_point(var, var->cast->h, type) == 0)
				draw_dir(var, var->cast->h, 0xFFFFFF);
		else if (type == MAP && var->cast->distv <= var->cast->disth
			&& valid_point(var, var->cast->v, type) == 0)
				draw_dir(var, var->cast->v, 0xFF0000);
	}
}

// void	find_wall_ray(t_var *var, int type)
// {
// 	float new_xv;
// 	float new_yv;
// 	float new_xh;
// 	float new_yh;
// 	float yav;
// 	float xav;
// 	float yah;
// 	float xah;
// 	float num_rays = 30;
// 	float dstv;
// 	float dsth;
// 	float ray_step = var->player->fov / num_rays;
// 	float ray_angle;
// 	float i = 0;
// 	// if (fabs(data.v_hit.x - data.start.x) < fabs(data.h_hit.x - data.start.x))
// 	while (i++ < num_rays)
// 	{
// 		ray_angle = (var->player->dir - (var->player->fov / 2) + (i * ray_step));
// 		printf("\nJoueur: %f %f\n", var->player->map_x, var->player->map_y);
// 		printf("\n\n\n%f\n", ray_angle);
// 		if (sin(ray_angle) < 0)
// 		{
// 			yah = type;
// 			new_yh = (floor(var->player->map_y / (float)type) * (float)type) + type;
// 		}
// 		else
// 		{
// 			yah = -type;
// 			new_yh = (floor(var->player->map_y / (float)type) * (float)type) - 1;
// 		}
// 		new_xh = var->player->map_x + ((var->player->map_y - new_yh) / tan(ray_angle));
// 		xah = (float)type / tan(ray_angle);
// 		if ((xah > 0 && cos(ray_angle) < 0) || (xah < 0 && cos(ray_angle) > 0))
// 			xah *= -1;
// 		printf("\nHITH: %f %f\n", new_xh, new_yh);
// 		while (1)
// 		{
// 			if (check_raycasting(new_yh, new_xh, type, var) == 0)
// 				break ;
// 			new_xh = new_xh + xah;
// 			new_yh = new_yh + yah;
// 		}
// 		dsth = distance(new_xh, new_yh, var->player->map_x, var->player->map_y);
// 		printf("step XH : %f\nstep YH : %f\ndistance horizonale : %f\n", xah, yah, dsth);

// 		if (cos(ray_angle) > 0)
// 		{
// 			xav = type;
// 			new_xv = (round(var->player->map_x / (float)type) * (float)type) + type;
// 		}
// 		else
// 		{
// 			xav = -type;
// 			new_xv = (round(var->player->map_x / (float)type) * (float)type) - 1;
// 		}
// 		new_yv = fabs(var->player->map_y + ((var->player->map_x - new_xv) * tan(ray_angle)));
// 		yav = (float)type * tan(ray_angle);
// 		if ((yav > 0 && sin(ray_angle) > 0) || (yav < 0 && sin(ray_angle) < 0))
// 			yav *= -1;
// 		while (1)
// 		{
// 			if (check_raycasting(new_yv, new_xv, type, var) == 0)
// 				break ;
// 			new_xv = new_xv + xav;
// 			new_yv = new_yv + yav;
// 		}
// 		printf("\nyav, rayangle: %f, %f\n", yav, ray_angle);
// 		printf("\nHITV: %f %f\n", new_xv, new_yv);
// 		dstv = distance(new_xv, new_yv, var->player->map_x, var->player->map_y);
// 		printf("\nstep XV : %f\nstep YV : %f\ndistance verticale : %f\n", xav, yav, dstv);
		

// 		if (dsth < dstv)
// 		{
// 			if ((new_yh > 0  && new_xh > 0) && new_xh < var->map->width * type && new_yh < var->map->height * type)
// 				draw_dir(var, new_yh, new_xh, 0xFF0000);
// 		}
// 		else if (dstv < dsth)
// 		{
// 			if ((new_yv > 0  && new_xv > 0) && new_xv < var->map->width * type && new_yv < var->map->height * type)
// 				draw_dir(var, new_yv, new_xv, 0xFFFFFF);
// 		}
// 	}
// }