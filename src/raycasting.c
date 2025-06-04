#include "cub3D.h"

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
			if (map_y / (int)GAME_sz < 0)
				map_y = 0;
			if (map_x / (int)GAME_sz < 0)
				map_x = 0;
			if (map_x / (int)GAME_sz >= var->map->width)
				map_x = var->map->width - 1;
			if (map_y / (int)GAME_sz >= var->map->height)
				map_y = var->map->height - 1;
			if (var->map->tab_map[map_y / (int)GAME_sz][map_x / (int)GAME_sz] == '1')
				hit = 1;
		}
		hit = 0;
		if (coordinates == 0)
		{
			dist = dist_x - delta_dist_x;
			if (step_x > 0)
				w_coordinates = EAST;
			else
				w_coordinates = WEST;
		}
		else
		{
			dist = dist_y - delta_dist_y;
			if (step_y > 0)
				w_coordinates = SOUTH;
			else
				w_coordinates = NORTH;
		}
		wall_h = (int)var->height / dist;

		draw_wall(var, wall_h, i, w_coordinates);
		i++;
	}
}

