#include "cub3D.h"

t_img	select_texture(t_var *var, t_cast *cast)
{
	t_img	texture;

	if (var->map->tab_map[(int)cast->map_y][(int)cast->map_x] == 'D')
		texture = var->door_t;
	else if (var->map->tab_map[(int)cast->map_y][(int)cast->map_x] == 'X')
		texture = var->exit_t;
	else if (cast->wall_dir == NORTH)
		texture = var->no_t;
	else if (cast->wall_dir == SOUTH)
		texture = var->so_t;
	else if (cast->wall_dir == EAST)
		texture = var->ea_t;
	else if (cast->wall_dir == WEST)
		texture = var->we_t;
	else
	{
		texture = var->no_t;
		return (ft_putstr_fd("Error: texture direction", 2), texture); /*VOIR SI FREE*/
	}
	return (texture);
}

void	find_pos_texture(t_var *var, t_cast *cast)
{
	double	pos;

	cast->texture = select_texture(var, cast);
	if (cast->wall_dir == EAST || cast->wall_dir == WEST)
		pos = var->player->pos_y + cast->dist * cast->ray_dir_y;
	else
		pos = var->player->pos_x + cast->dist * cast->ray_dir_x;
	pos -= floor(pos);
	cast->text_pos_x = (int)(pos * cast->texture.width);
	if (cast->wall_dir == SOUTH || cast->wall_dir == WEST)
		cast->text_pos_x = cast->texture.width - cast->text_pos_x - 1;
	if (cast->text_pos_x < 0)
		cast->text_pos_x = 0;
	if (cast->text_pos_x >= cast->texture.width)
		cast->text_pos_x = cast->texture.width - 1;
}

void	find_hit(t_var *var, t_cast *cast)
{
	while (1)
	{
		if (cast->dist_x < cast->dist_y)
		{
			cast->dist_x += cast->delta_dist_x;
			cast->map_x += cast->step_x;
			cast->coordinates = 0;
		}
		else
		{
			cast->dist_y += cast->delta_dist_y;
			cast->map_y += cast->step_y;
			cast->coordinates = 1;
		}
		if (check_in_map(var->map, cast->map_y, cast->map_x) != 1)
			return ;/*VOIR POUR FREE OU QUOI FAIRE SI RETURN*/
		if (var->map->tab_map[(int)cast->map_y][(int)cast->map_x] == '1'
			|| var->map->tab_map[(int)cast->map_y][(int)cast->map_x] == 'D'
			|| var->map->tab_map[(int)cast->map_y][(int)cast->map_x] == 'X')
		{
			if (cast->coordinates == 0)
				cast->dist = cast->dist_x - cast->delta_dist_x;
			else
				cast->dist = cast->dist_y - cast->delta_dist_y;
			cast->hit.x = var->player->pos_x + cast->dist * cast->ray_dir_x;
			cast->hit.y = var->player->pos_y + cast->dist * cast->ray_dir_y;
			break ;
		}
	}
}

void	init_dist_x_y(t_var *var, t_cast *cast)
{
	if (cast->ray_dir_x < 0)
	{
		cast->step_x = -1.f;
		cast->dist_x = (var->player->pos_x - cast->map_x) * cast->delta_dist_x;
	}
	else
	{
		cast->step_x = 1.f;
		cast->dist_x = (cast->map_x + 1.f - var->player->pos_x)
			* cast->delta_dist_x;
	}
	if (cast->ray_dir_y < 0)
	{
		cast->step_y = -1.f;
		cast->dist_y = (var->player->pos_y - cast->map_y) * cast->delta_dist_y;
	}
	else
	{
		cast->step_y = 1.f;
		cast->dist_y = (cast->map_y + 1.f - var->player->pos_y)
			* cast->delta_dist_y;
	}
}

void	init_cast_ray(t_var *var, t_cast *cast, int i)
{
	cast->camera = 2.0f * (double)i / var->width - 1.0f;
	cast->ray_dir_x = var->player->dir_x + var->player->plane_x
		* cast->camera;
	cast->ray_dir_y = var->player->dir_y + var->player->plane_y
		* cast->camera;
	cast->map_x = (int)var->player->pos_x;
	cast->map_y = (int)var->player->pos_y;
	if (cast->ray_dir_x == 0)
		cast->delta_dist_x = INFINITY;
	else
		cast->delta_dist_x = fabs(1.f / cast->ray_dir_x);
	if (cast->ray_dir_y == 0)
		cast->delta_dist_y = INFINITY;
	else
		cast->delta_dist_y = fabs(1.f / cast->ray_dir_y);
	init_dist_x_y(var, cast);
}

void	find_wall_dir(t_cast *cast)
{
	if (cast->coordinates == 0)
	{
		if (cast->step_x > 0)
			cast->wall_dir = EAST;
		else
			cast->wall_dir = WEST;
	}
	else
	{
		if (cast->step_y > 0)
			cast->wall_dir = SOUTH;
		else
			cast->wall_dir = NORTH;
	}
}

void	raycasting(t_var *var, t_cast *cast)
{
	double	i;

	i = 0;
	while (i < var->width)
	{
		init_cast_ray(var, cast, i);
		find_hit(var, cast);
		find_wall_dir(cast);
		cast->wall_h = (int)var->height / cast->dist;
		find_pos_texture(var, cast);
		draw_wall(var, var->cast, i);
		draw_dir(var, cast->hit, 0xf0eba8, i);
		i++;
	}
}
