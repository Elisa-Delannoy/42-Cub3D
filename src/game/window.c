/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:54:06 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 17:40:02 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	movement(t_var *var, t_map *map, t_player *player)
{
	double	speed;

	speed = player->speed;
	if (player->sprint == 1)
		speed *= 2;
	if (map->c_x == 1)
		check_end_game(var, player);
	if (player->m_up == 1)
		move_up(map, player, speed);
	if (player->m_down == 1)
		move_down(map, player, speed);
	if (player->m_left == 1)
		move_left(map, player, speed);
	if (player->m_right == 1)
		move_right(map, player, speed);
	if (player->t_left == 1)
		rotate(player, -0.03f);
	if (player->t_right == 1)
		rotate(player, +0.03f);
	if (player->o_c_door == 1)
		open_close_d(var, map);
}

void	draw_exit_game(t_var *var)
{
	if (var->exit == 0 && check_time(var) == 0)
	{
		mlx_put_image_to_window(var->mlx, var->win, var->img_g->img, 0, 0);
		mlx_put_image_to_window(var->mlx, var->win, var->img->img,
			((int)(var->width - (MAP_SZ * 10))), (int)(var->height
				- (MAP_SZ * 10)));
	}
	else if (var->exit == 1 && check_time(var) == 0)
	{
		draw_img_in_img(var, var->victory, 1, 1);
		mlx_put_image_to_window(var->mlx, var->win, var->img_g->img, 0, 0);
	}
	else if (check_time(var) == 1 && var->exit == 0)
	{
		draw_img_in_img(var, var->gameover, 1, 1);
		mlx_put_image_to_window(var->mlx, var->win, var->img_g->img, 0, 0);
	}
}

void	select_image_win(t_var *var)
{
	if (var->map->c_x == 1)
		draw_exit_game(var);
	else
	{
		mlx_put_image_to_window(var->mlx, var->win, var->img_g->img, 0, 0);
		mlx_put_image_to_window(var->mlx, var->win, var->img->img,
			((int)(var->width - (MAP_SZ * 10))), (int)(var->height
				- (MAP_SZ * 10)));
	}
}

int	gameplay(t_var *var)
{
	var->count++;
	if (var->count >= var->time)
	{
		var->count = 0;
		movement(var, var->map, var->player);
		if (var->player->mouse == 0)
			mlx_mouse_show(var->mlx, var->win);
		draw_game(var, var->img_g, var->light);
		draw_minimap(var);
		raycasting(var, var->cast);
		if ((var->on_off == -1 && var->a > 0)
			|| (var->on_off == 1 && var->a < 4))
			var->a += var->on_off;
		draw_img_in_img(var, var->torch[var->a], 550, 650);
		select_image_win(var);
		mlx_do_sync(var->mlx);
	}
	return (0);
}

int	setup_window(t_var *var)
{
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, (int)var->width, (int)var->height,
			"Exit the cavern !");
	var->light = init_light(var);
	var->cast = init_cast();
	var->minimap = init_minimap();
	var->batterie = set_timer(var);
	var->torch = init_torch(var);
	var->img = init_img();
	init_img_end(var);
	make_minimap(var);
	make_game(var);
	init_all_textures(var);
	mlx_hook(var->win, 17, 0, ft_free_all, var);
	mlx_mouse_hook(var->win, active_mouse, var);
	mlx_hook(var->win, MotionNotify, PointerMotionMask, mouse_movement, var);
	mlx_hook(var->win, KeyPress, KeyPressMask, key_press, var);
	mlx_hook(var->win, KeyRelease, KeyReleaseMask, key_release, var);
	mlx_loop_hook(var->mlx, gameplay, var);
	mlx_loop(var->mlx);
	return (0);
}
