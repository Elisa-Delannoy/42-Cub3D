/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:56:26 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 15:56:27 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (ft_putstr_fd("Error: texture direction", 2), texture);
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
