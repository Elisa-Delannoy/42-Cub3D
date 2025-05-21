#include "cub3D.h"

t_point	raycating_horizontal(t_var *var, t_cast *cast)
{
	t_point cell;
	
	if (sin(cast->ray) < 0)
	{
		cast->step_y = GAME_sz;
		cast->wall_dir_h = 'S';
	}
	else
	{
		cast->step_y = -GAME_sz;
		cast->wall_dir_h = 'N';
	}
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
	{
		cast->step_x = GAME_sz;
		cast->wall_dir_v = 'E';
	}
	else
	{
		cast->step_x = -GAME_sz;
		cast->wall_dir_v = 'W';
	}
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
	int	check;

	check = 0;
   	// if (fabs(cast->disth - cast->distv) <= 5)
	// {
	// 	// printf("i = %f diff dist = %f , wall dir = %c\n", i, cast->disth - cast->distv, cast->wall_dir);
	// 	check = 1;
	// 	cast->wall_dir = cast->wall_dir;
	// }
	// if (check == 1 && (cast->wall_dir == 'N' || cast->wall_dir == 'S'))
	// {
	// 	cast->wall_dir = cast->wall_dir_h;
	// 	draw_dir(var, cast->h, 0xf7f2a6);
	// 	wall_height(var, cast->disth, i);
	// }
	// else if ((check == 1 && (cast->wall_dir == 'E' || cast->wall_dir == 'W')))
	// {
	// 	cast->wall_dir = cast->wall_dir_v;
	// 	draw_dir(var, cast->v, 0xf7f2a6);
	// 	wall_height(var, cast->distv, i);
	// }
	// else if (fabs(cast->h.x - var->player->pos_x) <= fabs(cast->v.x - var->player->pos_x)
	// 		&& valid_point(var, cast->h) == 0)
	// {
	// 	// printf("i DANS H = %f diff dist = %f , wall dir = %c\n", i, cast->disth - cast->distv, cast->wall_dir);
	// 	cast->wall_dir = cast->wall_dir_h;
	// 	draw_dir(var, cast->h, 0xf7f2a6);
	// 	wall_height(var, cast->disth, i);
	// }
	// else if (valid_point(var, cast->v) == 0)
	// {
	// 	cast->wall_dir = cast->wall_dir_v;
	// 	draw_dir(var, cast->v, 0xf7f2a6);
	// 	wall_height(var, cast->distv, i);
	// }
	if (cast->disth < cast->distv)
	{
		if (1 ||valid_point(var, cast->h))
		{
			cast->wall_dir = cast->wall_dir_h;
			if(var->cast->wall_dir == 'N')
			{
				printf("P %.4f %.4f\n", var->player->pos_x, var->player->pos_y);
				printf("H %.4f P %.4f %.4f\n", cast->disth, cast->h.x, cast->h.y);
				printf("V %.4f P %.4f %.4f\n", cast->distv, cast->v.x, cast->v.y);
			}
			draw_dir(var, cast->h, 0xf7f2a6);
			wall_height(var, cast->disth, i);
		}else
			printf("INVALID\n");

	}
	else
	{
		if (1 ||valid_point(var, cast->v))
		{
			cast->wall_dir = cast->wall_dir_v;
			draw_dir(var, cast->v, 0xf7f2a6);
			wall_height(var, cast->distv, i);
		}
		else
			printf("INVALID\n");
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
		// printf("i = %d h.x = %f, h.y = %f, pos.x = %f, pos.y = %f\n", i, var->cast->h.x, var->cast->h.y, var->player->pos_x, var->player->pos_y);
		var->cast->disth = distance(var->cast->h, var->player->pos_x, var->player->pos_y);
		// printf("v. = %f, v.y = %f, pos.x = %f, pos.y = %f\n", var->cast->v.x, var->cast->v.y, var->player->pos_x, var->player->pos_y);
		var->cast->distv = distance(var->cast->v, var->player->pos_x, var->player->pos_y);
		// printf("dist %f\n", var->cast->disth - var->cast->distv);
		map_print(var, var->cast, var->width - i);
		i++;
	}
}
