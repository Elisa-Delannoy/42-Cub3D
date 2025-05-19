#include "cub3D.h"

t_point	raycating_horizontal(t_var *var, t_cast *cast)
{
	t_point cell;
	
	if (sin(cast->ray) < 0)
		cast->step_y = GAME_sz;
	else
		cast->step_y = -GAME_sz;
	if (sin(cast->ray) < 0)
		cell.y = (floor(var->player->pos_y / GAME_sz) * GAME_sz) + GAME_sz;
	else
		cell.y = (floor(var->player->pos_y / GAME_sz) * GAME_sz) - 1.0f;
	cell.x = var->player->pos_x + ((var->player->pos_y - cell.y) / cast->tan);
	cast->step_x = (float)(GAME_sz / cast->tan);
	if ((cast->step_x > 0 && cos(cast->ray) < 0) || (cast->step_x < 0 && cos(cast->ray) > 0))
		cast->step_x *= -1.0f;
	while (1)
	{
		if (check_raycasting(cell.y, cell.x, var) == 0)
			break ;
		cell.x += cast->step_x;
		cell.y += cast->step_y;
	}
	return (cell);
}

t_point	raycating_vertical(t_var *var, t_cast *cast)
{
	t_point cell;

	if (cos(cast->ray) > 0)
		cast->step_x = GAME_sz;
	else
		cast->step_x = -GAME_sz;
	if (cos(cast->ray) > 0)
		cell.x = (floor(var->player->pos_x / GAME_sz) * GAME_sz) + GAME_sz;
	else
		cell.x = (floor(var->player->pos_x / GAME_sz) * GAME_sz) - 1.0f;
	cell.y = var->player->pos_y + ((var->player->pos_x - cell.x) * cast->tan);
	cast->step_y = (float)(GAME_sz * cast->tan);
	if ((cast->step_y >= 0 && sin(cast->ray) >= 0) || (cast->step_y <= 0 && sin(cast->ray) <= 0))
		cast->step_y *= -1.0f;
	while (1)
	{
		if (check_raycasting(cell.y, cell.x, var) == 0)
			break ;
		cell.x += cast->step_x;
		cell.y += cast->step_y;
	}
	return(cell);
}

void	map_print(t_var *var, t_cast *cast, float i)
{
	if (fabs(cast->h.x - var->player->pos_x) < fabs(cast->v.x - var->player->pos_x)
			&& valid_point(var, cast->h) == 0)
	{
		draw_dir(var, cast->h, 0xFFFFFF);
		wall_height(var, cast->disth, i);
	}
	else if (valid_point(var, cast->v) == 0)
	{
		// if (cos(cast->ray) <= 0)
		// {
		// 	while (var->map->tab_map[(int)(cast->v.y / GAME_sz)][(int)(((cast->v.x) / GAME_sz))] == '1')
		// 	{
		// 		cast->v.x++;
				printf("v.x map %f v.x case %d, -1 %d\n", cast->v.x, (int)(cast->v.x / 64), (int)(cast->v.x - 1)/64) ;
			// }
			// cast->v.x--;
		// }
		if (valid_point(var, cast->v) == 0)
		{
			draw_dir(var, cast->v, 0xFFFFFF);
			wall_height(var, cast->distv, i);
		}
	}
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
		var->cast->disth = distance(var->cast->h, var->player->pos_x, var->player->pos_y);
		var->cast->distv = distance(var->cast->v, var->player->pos_x, var->player->pos_y);	
		map_print(var, var->cast, var->width - i);
		i++;
	}
}
