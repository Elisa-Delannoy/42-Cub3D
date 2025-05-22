#include "cub3D.h"

t_point	raycating_horizontal(t_var *var, t_cast *cast)
{
	t_point cell;
	
	if (sin(cast->ray) < 0)
	{
		cast->step_hy = GAME_sz;
		cast->wall_dir_h = 'S';
	}
	else
	{
		cast->step_hy = -GAME_sz;
		cast->wall_dir_h = 'N';
	}
	if (sin(cast->ray) < 0)
		cell.y = (floor(var->player->pos_y / GAME_sz) * GAME_sz) + GAME_sz;
	else
		cell.y = (floor(var->player->pos_y / GAME_sz) * GAME_sz) - 1.0f;
	cell.x = var->player->pos_x + ((var->player->pos_y - cell.y) / cast->tan);
	cast->step_hx = (float)(GAME_sz / cast->tan);
	if ((cast->step_hx > 0 && cos(cast->ray) < 0) || (cast->step_hx < 0 && cos(cast->ray) > 0))
		cast->step_hx *= -1.0f;
	// if (check_raycasting(cell.y, cell.x, var) != 0)
	// {
	// 	cell.x += cast->step_hx;
	// 	cell.y += cast->step_hy;
	// }
	return (cell);
}

t_point	raycating_vertical(t_var *var, t_cast *cast)
{
	t_point cell;

	if (cos(cast->ray) > 0)
	{
		cast->step_vx = GAME_sz;
		cast->wall_dir_v = 'E';
	}
	else
	{
		cast->step_vx = -GAME_sz;
		cast->wall_dir_v = 'W';
	}
	if (cos(cast->ray) > 0)
		cell.x = (floor(var->player->pos_x / GAME_sz) * GAME_sz) + GAME_sz;
	else
		cell.x = (floor(var->player->pos_x / GAME_sz) * GAME_sz) - 1.0f;
	cell.y = var->player->pos_y + ((var->player->pos_x - cell.x) * cast->tan);
	cast->step_vy = (float)(GAME_sz * cast->tan);
	if ((cast->step_vy >= 0 && sin(cast->ray) >= 0) || (cast->step_vy <= 0 && sin(cast->ray) <= 0))
		cast->step_vy *= -1.0f;
	// if (check_raycasting(cell.y, cell.x, var) != 0)
	// {
	// 	cell.x += cast->step_vx;
	// 	cell.y += cast->step_vy;
	// }
	return(cell);
}

void	map_print(t_var *var, t_cast *cast, float i)
{

	draw_dir(var, cast->w, 0xf7f2a6);
	wall_height(var, cast->dist, i);
}


void	raycasting(t_var *var)
{
	int i;
	float	ray_step;

	ray_step = var->player->fov / var->width;
	i = 0;
	// while (i < 1)
	while (i < var->width)
	{
		var->cast->ray = (var->player->dir - (var->player->fov / 2) + (i * ray_step));
		var->cast->tan = tan(var->cast->ray);
		var->cast->h = raycating_horizontal(var, var->cast);
		var->cast->v = raycating_vertical(var, var->cast);
		var->cast->w = find_hit(var, var->cast);

		printf("i = %d x = %f, y = %f, pos.x = %f, pos.y = %f\n", i, var->cast->w.x, var->cast->w.y, var->player->pos_x, var->player->pos_y);
		// var->cast->disth = distance(var->cast->h, var->player->pos_x, var->player->pos_y);
		// printf("v. = %f, v.y = %f, pos.x = %f, pos.y = %f\n", var->cast->v.x, var->cast->v.y, var->player->pos_x, var->player->pos_y);
		// var->cast->distv = distance(var->cast->v, var->player->pos_x, var->player->pos_y);
		var->cast->dist = distance(var->cast->w, var->player->pos_x, var->player->pos_y);
		printf("dist %f\n", var->cast->dist);

		map_print(var, var->cast, var->width - i);
		i++;
	}
}
