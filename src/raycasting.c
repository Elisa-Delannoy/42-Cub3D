#include "cub3D.h"

int	find_pos_texture(t_var *var, double ray_x, double ray_y, double dist, int w_coordinates)
{
	double	pos;
	int		texture_x;

	if (w_coordinates == EAST || w_coordinates == WEST)
		pos = var->player->pos_y + dist * ray_y;
	else
		pos = var->player->pos_x + dist * ray_x;
	pos -= floor(pos);
	texture_x = (int)(pos * var->no_t.width); /*mettre autre largeur*/
	if (w_coordinates == SOUTH || w_coordinates == EAST)
		texture_x = var->no_t.width - texture_x - 1;
	if (texture_x < 0)
		texture_x = 0;
	if (texture_x >= var->no_t.width)
		texture_x = var->no_t.width - 1;
	return (texture_x);
}

void	raycasting(t_var *var)
{
	t_point	hit;

	double 	i;
	double	camera;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	dist_x;
	double	dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double		step_x;
	double		step_y;
	int		hit_w;
	int		coordinates;
	double	dist;
	int		wall_h;

	int		texture_x;

	int		w_coordinates;


	i = 0;
	hit_w = 0;
	coordinates = 0;
	while (i < var->width)
	{
		camera = 2.0f * i / var->width - 1.0f;
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

		while (hit_w == 0)
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
			{
				hit_w = 1;
				hit.x = map_x;
				hit.y = map_y;
			}
		}
		printf("x = %f\n", hit.x);
		printf("y = %f\n", hit.y);
		hit_w = 0;
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


		// printf("dist = %f\n", dist);
		// printf("x = %f\n", ray_x);
		// printf("y = %f\n", ray_y);
		// printf("coord = %d\n", w_coordinates);
		texture_x = find_pos_texture(var, ray_x, ray_y, dist, w_coordinates);
		// printf("texture_x = %d\n", texture_x);
		draw_wall(var, wall_h, i, w_coordinates, texture_x);

		i++;
	}
}


