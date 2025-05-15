#include "cub3D.h"

t_point	raycating_horizontal(t_var *var, t_cast *cast, float type)
{
	t_point cell;
	
	if (sin(cast->ray) < 0)
		cast->step_y = type;
	else
		cast->step_y = -type;
	if (sin(cast->ray) < 0)
		cell.y = (floor(var->player->map_y / type) * type) + type;
	else
		cell.y = (floor(var->player->map_y / type) * type) - 1;
	cell.x = var->player->map_x + ((var->player->map_y - cell.y) / cast->tan);
	cast->step_x = (float)type / cast->tan;
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
		cast->step_x = type;
	else
		cast->step_x = -type;
	if (cos(cast->ray) > 0)
		cell.x = (floor(var->player->map_x / type) * type) + type;
	else
		cell.x = (floor(var->player->map_x / type) * type) - 1;
	cell.y = var->player->map_y + ((var->player->map_x - cell.x) * cast->tan);
	cast->step_y = (float)type * cast->tan;
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

void	map_print(t_var *var, t_cast *cast, float type, float i)
{
	if (cast->disth < cast->distv
			&& valid_point(var, cast->h, type) == 0)
	{
		draw_dir(var, cast->h, 0xFFFFFF);
		wall_height(var, cast->disth * 3.2, i);
	}
	else if (cast->distv <= cast->disth
		&& valid_point(var, cast->v, type) == 0)
	{
		draw_dir(var, cast->v, 0xFF0000);
		wall_height(var, cast->distv * 3.2, i);
	}
}

void	raycasting(t_var *var, float type)
{
	int i;
	float	ray_step;

	ray_step = var->player->fov / 1900.0f;
	i = 0;
	while (i++ < 1900)
	{
		var->cast->ray = (var->player->dir - (var->player->fov / 2) + (i * ray_step));
		var->cast->tan = tan(var->cast->ray);
		var->cast->h = raycating_horizontal(var, var->cast, type);
		var->cast->v = raycating_vertical(var, var->cast, type);
		var->cast->disth = distance(var->cast->h, var->player->map_x, var->player->map_y);
		var->cast->distv = distance(var->cast->v, var->player->map_x, var->player->map_y);		
		map_print(var, var->cast, type, 1900 - i);
	}
}
