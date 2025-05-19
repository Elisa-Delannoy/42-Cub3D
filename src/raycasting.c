#include "cub3D.h"

t_point	raycating_horizontal(t_var *var, t_cast *cast, float type)
{
	t_point cell;
	
	if (sin(cast->ray) < 0)
		cast->step_y = type;
	else
		cast->step_y = -type;
	if (sin(cast->ray) < 0)
		cell.y = (floor(var->player->pos_y / type) * type) + type;
	else
		cell.y = (floor(var->player->pos_y / type) * type) - 1.0f;
	cell.x = var->player->pos_x + ((var->player->pos_y - cell.y) / cast->tan);
	cast->step_x = (float)type / cast->tan;
	if ((cast->step_x > 0 && cos(cast->ray) < 0) || (cast->step_x < 0 && cos(cast->ray) > 0))
		cast->step_x *= -1.0f;
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
		cell.x = (floor(var->player->pos_x / type) * type) + type;
	else
		cell.x = (floor(var->player->pos_x / type) * type) - 1.0f;
	cell.y = var->player->pos_y + ((var->player->pos_x - cell.x) * cast->tan);
	cast->step_y = (float)type * cast->tan;
	if ((cast->step_y >= 0 && sin(cast->ray) >= 0) || (cast->step_y <= 0 && sin(cast->ray) <= 0))
		cast->step_y *= -1.0f;
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
	if (fabs(cast->h.x - var->player->pos_x) < fabs(cast->v.x - var->player->pos_x)
			&& valid_point(var, cast->h, type) == 0)
	{
		draw_dir(var, cast->h, 0xFFFFFF);
		wall_height(var, cast->disth, i);
	}
	else if (valid_point(var, cast->v, type) == 0)
	{
		// printf("hx %f\n", cast->h.x);
		// printf("hy %f\n", cast->h.y);
		// printf("vx %f\n", cast->v.x);
		// printf("vy %f\n", cast->v.y);
		// printf("play x %f\n", var->player->pos_x);
		// printf("play y %f\n", var->player->pos_y);
		// printf("ray angle %f\n", var->cast->ray);
		draw_dir(var, cast->v, 0xFFFFFF);
		wall_height(var, cast->distv, i);
	}
}

void	raycasting(t_var *var, float type)
{
	int i;
	float	ray_step;

	ray_step = var->player->fov / var->width;
	i = 0;
	while (i < var->width)
	{
		var->cast->ray = (var->player->dir - (var->player->fov / 2) + (i * ray_step));
		var->cast->tan = tan(var->cast->ray);
		var->cast->h = raycating_horizontal(var, var->cast, type);
		var->cast->v = raycating_vertical(var, var->cast, type);
		var->cast->disth = distance(var->cast->h, var->player->pos_x, var->player->pos_y);
		var->cast->distv = distance(var->cast->v, var->player->pos_x, var->player->pos_y);		
		map_print(var, var->cast, type, var->width - i);
		i++;
	}
}
