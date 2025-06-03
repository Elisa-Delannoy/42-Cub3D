#include "cub3D.h"

// t_point	raycating_horizontal(t_var *var, t_cast *cast)
// {
// 	t_point cell;
	
// 	if (sin(cast->ray) < 0)
// 		cast->step_hy = GAME_sz;
// 	else
// 		cast->step_hy = -GAME_sz;
// 	if (sin(cast->ray) < 0)
// 		cell.y = (floor(var->player->pos_y / GAME_sz) * GAME_sz) + GAME_sz;
// 	else
// 		cell.y = (floor(var->player->pos_y / GAME_sz) * GAME_sz) - 1.0f;
// 	cell.x = var->player->pos_x + ((var->player->pos_y - cell.y) / cast->tan);
// 	cast->step_hx = (double)(GAME_sz / cast->tan);
// 	if ((cast->step_hx > 0 && cos(cast->ray) < 0) || (cast->step_hx < 0 && cos(cast->ray) > 0))
// 		cast->step_hx *= -1.0f;
// 	return (cell);
// }

// t_point	raycating_vertical(t_var *var, t_cast *cast)
// {
// 	t_point cell;

// 	if (cos(cast->ray) > 0)
// 		cast->step_vx = GAME_sz;
// 	else
// 		cast->step_vx = -GAME_sz;
// 	if (cos(cast->ray) > 0)
// 		cell.x = (floor(var->player->pos_x / GAME_sz) * GAME_sz) + GAME_sz;
// 	else
// 		cell.x = (floor(var->player->pos_x / GAME_sz) * GAME_sz) - 1.0f;
// 	cell.y = var->player->pos_y + ((var->player->pos_x - cell.x) * cast->tan);
// 	cast->step_vy = (double)(GAME_sz * cast->tan);
// 	if ((cast->step_vy >= 0 && sin(cast->ray) >= 0) || (cast->step_vy <= 0 && sin(cast->ray) <= 0))
// 		cast->step_vy *= -1.0f;
// 	return(cell);
// }


// void	map_print(t_var *var, t_cast *cast, double i)
// {
// 	draw_dir(var, cast->w, 0xf7f2a6);
// 	wall_height(var, cast->dist, i);
// }



// t_point	find_hit(t_var *var, t_cast *cast)
// {
// 	int	check_h;
// 	int	check_v;

// 	while (1)
// 	{
// 		if (fabs(cast->h.x - var->player->pos_x) < fabs(cast->v.x - var->player->pos_x))
// 		{
// 			check_h = check_raycasting(cast->h.y / GAME_sz, cast->h.x / GAME_sz, var);
// 			if (check_h == 0)
// 			{
// 				if (sin(cast->ray) < 0)
// 					cast->wall_dir = SOUTH;
// 				else
// 					cast->wall_dir = NORTH;
// 				return (cast->h);
// 			}
// 			else
// 			{
// 				cast->h.x += cast->step_hx;
// 				cast->h.y += cast->step_hy;
// 			}
// 		}
// 		else
// 		{
// 			check_v = check_raycasting(cast->v.y / GAME_sz, cast->v.x / GAME_sz, var);
// 			if (check_v == 0)
// 			{
// 				if (cos(cast->ray) < 0)
// 					cast->wall_dir = WEST;
// 				else
// 					cast->wall_dir = EAST;
// 				return (cast->v);
// 			}
// 			else
// 			{
// 				cast->v.x += cast->step_vx;
// 				cast->v.y += cast->step_vy;
// 			}
// 		}
// 		// printf("check h = %d, check v = %d\n", check_h, check_v);
// 		// printf("hy %f\n", cast->step_hy);
// 		// printf("vx %f\n", cast->step_vx);
// 		// printf("vy %f\n", cast->step_vy);
// 		// printf("hx %f\n", cast->step_hx);

// 		// if (check_h == 0 && check_v == 0)
// 		// {
// 		// 	if (distance(cast->h, var->player->pos_x, var->player->pos_y) < distance(cast->v, var->player->pos_x, var->player->pos_y))
// 		// 	{
// 		// 		if (sin(cast->ray) < 0)
// 		// 			cast->wall_dir = SOUTH;
// 		// 		else
// 		// 			cast->wall_dir = NORTH;
// 		// 		return (cast->h);
// 		// 	}
// 		// 	else
// 		// 	{
// 		// 		if (cos(cast->ray) < 0)
// 		// 			cast->wall_dir = WEST;
// 		// 		else
// 		// 			cast->wall_dir = EAST;
// 		// 		return (cast->v);
// 		// 	}
// 		// }
// 		// else if (check_h == 0)
// 		// {
// 		// 	if (sin(cast->ray) < 0)
// 		// 		cast->wall_dir = SOUTH;
// 		// 	else
// 		// 		cast->wall_dir = NORTH;
// 		// 	return (cast->h);
// 		// }
// 		// else if (check_v == 0)
// 		// {
// 		// 	if (cos(cast->ray) < 0)
// 		// 		cast->wall_dir = WEST;
// 		// 	else
// 		// 		cast->wall_dir = EAST;
// 		// 	return (cast->v);
// 		// }
// 		// else
// 		// {
// 		// 	cast->h.x += cast->step_hx;
// 		// 	cast->h.y += cast->step_hy;
// 		// 	// printf("hx %f\n", cast->h.x);
// 		// 	// printf("hy %f\n\n", cast->h.y);
// 		// 	cast->v.x += cast->step_vx;
// 		// 	cast->v.y += cast->step_vy;
// 		// 	// printf("vx %f\n", cast->v.x);
// 		// 	// printf("vy %f\n\n", cast->v.y);
// 		// }
// 			// if (fabs(cast->h.x - var->player->pos_x) <= fabs(cast->v.x - var->player->pos_x))
// 	}
// }

void	raycasting(t_var *var)
{
	float 	i;
	float	camera;
	float	ray_x;
	float	ray_y;
	int		map_x;
	int		map_y;
	float	dist_x;
	float	dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		coordinates;
	float	dist;
	int		wall_h;

	int		w_coordinates;
	int		angle;



	i = 0;
	hit = 0;
	coordinates = 0;
	while (i < var->width)
	{
		camera = 2 * i / var->width - 1;
		ray_x = var->player->dir_x + var->player->plane_x * camera;
		ray_y = var->player->dir_y + var->player->plane_y * camera;
		map_x = (int)var->player->pos_x;
		map_y = (int)var->player->pos_y;

		if (ray_x == 0)
			delta_dist_x = INFINITY;
		else
			delta_dist_x = fabs(1 / ray_x);
		if (ray_y == 0)
			delta_dist_y = INFINITY;
		else
			delta_dist_y = fabs(1 / ray_y);

		if (ray_x < 0)
		{
			step_x = -GAME_sz;
			dist_x = (var->player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = GAME_sz;
			dist_x = (map_x + GAME_sz - var->player->pos_x) * delta_dist_x;
		}
		if (ray_y < 0)
		{
			step_y = -GAME_sz;
			dist_y = (var->player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = GAME_sz;
			dist_y = (map_y + GAME_sz - var->player->pos_y) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (dist_x < dist_y)
			{
				dist_x += delta_dist_x;
				map_x += step_x;
				coordinates = 0;
			}
			else
			{
				dist_y += delta_dist_y;
				map_y += step_y;
				coordinates = 1;
			}

			// printf("map_y %d\n", map_y / (int)GAME_sz);
			// printf("map_x %d\n", map_x /  (int)GAME_sz);
			// printf("tab %c\n", var->map->tab_map[map_y / (int)GAME_sz][map_x / (int)GAME_sz]);
			if (map_y / (int)GAME_sz < 0)
				map_y = 0;
			if (map_x / (int)GAME_sz < 0)
				map_x = 0;
			if (map_x / (int)GAME_sz >= var->map->width)
				map_x = var->map->width - 1;
			if (map_y / (int)GAME_sz >= var->map->height)
				map_y = var->map->height - 1;
// 		return (0);
			if (var->map->tab_map[map_y / (int)GAME_sz][map_x / (int)GAME_sz] == '1')
				hit = 1;
			// printf("hit %d\n", hit);
		}
		hit = 0;
		angle = sin(atan2(var->player->dir_y, var->player->dir_x));
		if (coordinates == 0)
		{
			dist = dist_x - delta_dist_x;
			if (sin(angle) > 0)
				w_coordinates = NORTH;
			else
				w_coordinates = SOUTH;
		}
		else
		{
			dist = dist_y - delta_dist_y;
			if (cos(angle) > 0)
				w_coordinates = EAST;
			else
				w_coordinates = WEST;
		}
		wall_h = (int)var->height / dist;

		draw_wall(var, wall_h, i, w_coordinates);
		i++;
	}
}






		// printf("\ni = %d\n", i);
		// var->cast->ray = (var->player->dir - (var->player->fov / 2) + (i * ray_step));
		// var->cast->tan = tan(var->cast->ray);
		// var->cast->h = raycating_horizontal(var, var->cast);
		// var->cast->v = raycating_vertical(var, var->cast);
		// var->cast->w = find_hit(var, var->cast);
		// var->cast->disth = distance(var->cast->h, var->player->pos_x, var->player->pos_y);
		// var->cast->distv = distance(var->cast->v, var->player->pos_x, var->player->pos_y);
		// if (var->cast->wall_dir == NORTH)
		// {
		// 	printf("\ni = %f\n", i);
		// 	printf("x = %f, y = %f, | pos.x = %f, pos.y = %f\n", var->cast->w.x, var->cast->w.y, var->player->pos_x, var->player->pos_y);
		// 	printf("v.x = %f, v.y = %f\n", var->cast->v.x, var->cast->v.y);
		// 	printf("dist H %f, dist V %f\n", var->cast->disth, var->cast->distv);
			
		// }
		// var->cast->dist = distance(var->cast->w, var->player->pos_x, var->player->pos_y);

		// map_print(var, var->cast, var->width - i);
