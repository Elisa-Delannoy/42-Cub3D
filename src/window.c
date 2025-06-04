#include "cub3D.h"

int clear_all(t_var *var)
{
	mlx_do_key_autorepeaton(var->mlx);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	exit (EXIT_SUCCESS);
	return (0);
}

void	rotate(t_player *player, float angle)
{
	float	previous_dir_x;
	float	previous_plane_x;

	previous_dir_x = player->dir_x;
	previous_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = previous_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = previous_plane_x * sin(angle) + player->plane_y * cos(angle);
}

void	movement(t_map *map, t_player *player)
{
	float	speed;

	speed = player->speed;
	if (player->sprint == 1)
		speed *= 2;
	if (player->m_up == 1)
		move_up(map, player, speed);
	if (player->m_down == 1)
		move_down(map, player, speed);
	if (player->m_left == 1)
		move_left(map, player, speed);
	if (player->m_right == 1)
		move_right(map, player, speed);
	if (player->t_left == 1)
		rotate(player, -0.05f);
	if (player->t_right == 1)
		rotate(player, +0.05f);
}

int	gameplay(t_var *var)
{
	var->count++;
	if (var->count >= var->time)
	{
		var->count = 0;
		mlx_put_image_to_window(var->mlx, var->win, var->img_g->img, 0, 0);
		mlx_put_image_to_window(var->mlx, var->win, var->img->img, ((int)(var->width - (MAP_sz * var->map->width))), (int)(var->height - (MAP_sz * var->map->height)));
		// draw_dir(var, 1920 - ((34 - var->player->map_y - 0.5) * 20), 1080 - ((14 - var->player->map_x - 0.5) * 20), 0xFF0140);
		// find_wall_ray(var, MAP);
		movement(var->map, var->player);
		draw_game(var->img_g, var);
		draw_minimap(var);
		// draw_player(var, 0xFF0140, var->player->pos_y / var->map->g_to_m, var->player->pos_x / var->map->g_to_m);
		raycasting(var);
		// find_wall_ray(var, GAME);
	}
	return(0);
}

int	key_press(int keycode, t_var *var)
{
	// draw_player(var, 0xFF0140, var->player->pos_y / var->map->g_to_m, var->player->pos_x / var->map->g_to_m);
	if (keycode == ESC)
		clear_all(var);
	if (keycode == UP && var->player)
		var->player->m_up = 1;
	if (keycode == DOWN)
		var->player->m_down = 1;
	if (keycode == LEFT)
		var->player->m_left = 1;
	if (keycode == RIGHT)
		var->player->m_right = 1;
	if (keycode == SPRINT)
		var->player->sprint = 1;
	if (keycode == TURN_L)
		var->player->t_left = 1;
	if (keycode == TURN_R)
		var->player->t_right = 1;
	return (0);
}

int	key_release(int keycode, t_var *var)
{
	if (keycode == UP)
		var->player->m_up = 0;
	if (keycode == DOWN)
		var->player->m_down = 0;
	if (keycode == LEFT)
		var->player->m_left = 0;
	if (keycode == RIGHT)
		var->player->m_right = 0;
	if (keycode == SPRINT)
		var->player->sprint = 0;
	if (keycode == TURN_L)
		var->player->t_left = 0;
	if (keycode == TURN_R)
		var->player->t_right = 0;
	return (0);
}

t_cast	*init_cast(void)
{
	t_cast	*cast;

	cast = malloc(sizeof(t_cast));
	return (cast);
}

int	setup_window(t_var *var)
{
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, (int)var->width, (int)var->height, "Exit the cavern !");
	var->cast = init_cast();
	make_minimap(var);
	make_game(var);
	// printf("x =%f\n", var->player->map_x);
	// printf("y =%f\n", var->player->map_y);
	mlx_hook(var->win, 17, 0, clear_all, var);
	mlx_hook(var->win, 2, 1L << 0, key_press, var);
	mlx_hook(var->win, 3, 1L << 1, key_release, var);
	mlx_loop_hook(var->mlx, gameplay, var);
	// mlx_hook(var->win, 2, 1L << 0, key_hook, g);
	mlx_loop(var->mlx);
	return (0);
}
