// #include "cub3D.h"

// void	raycating_horizontal(t_var *var, t_cast *cast)
// {
// 	cast->step_y = GAME_sz;
// 	cast->step_x = GAME_sz;

// 	if (sin(cast->ray) <= 0)
// 		cast->step_y *= -1;
// 	if (cos(cast->ray) <= 0)
// 		cast->step_x *= -1;
// 	cast->v.x = floor(var->player->pos_x / GAME_sz) * GAME_sz;
// 	if (cast->step_x > 0)
// 		cast->v.x += GAME_sz;
// 	cast->v.y = var->player->pos_y + (cast->v.x - var->player->pos_x) * cast->tan;
// 	cast->h.y = floor(var->player->pos_y / GAME_sz) * GAME_sz;
// 	if (cast->step_y > 0)
// 		cast->h.y += GAME_sz;
// 	cast->h.x = var->player->pos_x + (cast->h.y - var->player->pos_y) / cast->tan;
// }

// // t_point	raycating_vertical(t_var *var, t_cast *cast)
// // {
// // 	t_point cell;

// // 	if (cos(cast->ray) > 0)
// // 		cast->step_vx = GAME_sz;
// // 	else
// // 		cast->step_vx = -GAME_sz;
// // 	if (cos(cast->ray) > 0)
// // 		cell.x = (floor(var->player->pos_x / GAME_sz) * GAME_sz) + GAME_sz;
// // 	else
// // 		cell.x = (floor(var->player->pos_x / GAME_sz) * GAME_sz) - 1.0f;
// // 	cell.y = var->player->pos_y + ((var->player->pos_x - cell.x) * cast->tan);
// // 	cast->step_vy = (double)(GAME_sz * cast->tan);
// // 	if ((cast->step_vy >= 0 && sin(cast->ray) >= 0) || (cast->step_vy <= 0 && sin(cast->ray) <= 0))
// // 		cast->step_vy *= -1.0f;
// // 	return(cell);
// // }



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
// 		if (fabs(cast->h.x - var->player->pos_x) 
// 			< fabs(cast->v.x - var->player->pos_x))
// 		{
// 			if (cast->step_y < 0)
// 				check_h = check_raycasting(floor(cast->h.y / GAME_sz) - 1, floor(cast->h.x / GAME_sz), var);
// 			else
// 				check_h = check_raycasting(floor(cast->h.y / GAME_sz), floor(cast->h.x / GAME_sz), var);
// 			if (check_h == 0)
// 				return (cast->h);
// 			else
// 			{
// 				cast->h.x += cast->step_x;
// 				cast->h.y += cast->step_x * cast->tan;
// 			}
// 		}
// 		else
// 		{
// 			if (cast->step_x < 0)
// 				check_v = check_raycasting(floor(cast->v.y / GAME_sz), floor(cast->v.x / GAME_sz) - 1, var);
// 			else
// 				check_v = check_raycasting(floor(cast->v.y / GAME_sz), floor(cast->v.x / GAME_sz), var);
// 			if (check_v == 0)
// 				return (cast->v);
// 			else
// 			{
// 				cast->v.x += cast->step_y / cast->tan;
// 				cast->v.y += cast->step_y;
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

// void	raycasting(t_var *var)
// {
// 	double i;
// 	double	ray_step;

// 	ray_step = var->player->fov / var->width;
// 	i = 0;
// 	// while (i < 1)
// 	while (i < var->width)
// 	{
// 		// printf("\ni = %d\n", i);
// 		var->cast->ray = (var->player->dir - (var->player->fov / 2) + (i * ray_step));
// 		var->cast->tan = tan(var->cast->ray);
// 		raycating_horizontal(var, var->cast);
// 		// var->cast->v = raycating_vertical(var, var->cast);
// 		var->cast->w = find_hit(var, var->cast);

// 		// printf("i = %d x = %f, y = %f, pos.x = %f, pos.y = %f\n", i, var->cast->w.x, var->cast->w.y, var->player->pos_x, var->player->pos_y);
// 		// var->cast->disth = distance(var->cast->h, var->player->pos_x, var->player->pos_y);
// 		// printf("v. = %f, v.y = %f, pos.x = %f, pos.y = %f\n", var->cast->v.x, var->cast->v.y, var->player->pos_x, var->player->pos_y);
// 		// var->cast->distv = distance(var->cast->v, var->player->pos_x, var->player->pos_y);
// 		var->cast->dist = distance(var->cast->w, var->player->pos_x, var->player->pos_y);
// 		// printf("dist %f\n", var->cast->dist);

// 		map_print(var, var->cast, var->width - i);
// 		i++;
// 	}
// }
