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
	if ((cast->step_y >= 0 && sin(cast->ray) >= 0) || (cast->step_y <= 0 && sin(cast->ray) <= 0))
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

void	raycasting(t_var *var, int type)
{
	int i;
	float	ray_step;

	ray_step = var->player->fov /1900;
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
				{
					draw_dir(var, var->cast->h, 0xFFFFFF);
					wall_height(var, var->cast->disth, i);
				}
		else if (type == MAP && var->cast->distv <= var->cast->disth
			&& valid_point(var, var->cast->v, type) == 0)
				{
					draw_dir(var, var->cast->v, 0xFF0000);
					wall_height(var, var->cast->distv, i);
				}
		// if (type == MAP
		// 	&& valid_point(var, var->cast->v, type) == 0)
	}
}
