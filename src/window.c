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
		draw_game(var->img_g, var->height, var->width);
		draw_minimap(var);
		draw_player(var, 0xFF0140, var->player->pos_y / var->map->g_to_m, var->player->pos_x / var->map->g_to_m);
		raycasting(var);
		// find_wall_ray(var, GAME);
	}
	return(0);
}

int	key_hook(int keycode, t_var *var)
{
	draw_player(var, 0xFF0140, var->player->pos_y / var->map->g_to_m, var->player->pos_x / var->map->g_to_m);
	if (keycode == ESC)
		clear_all(var);
	if (keycode == UP)
	{
		var->player->pos_x += cos(var->player->dir) * 1;
		var->player->pos_y -= sin(var->player->dir) * 1;
	}
	if (keycode == DOWN)
	{
		var->player->pos_x -= cos(var->player->dir) * 1;
		var->player->pos_y += sin(var->player->dir) * 1;
	}
	if (keycode == LEFT)
	{
		var->player->pos_x += cos(var->player->dir + (PI/2)) * 1;
		var->player->pos_y += sin(var->player->dir - (PI/2)) * 1;
	}	
	if (keycode == RIGHT)
	{
		var->player->pos_x += cos(var->player->dir - (PI/2)) * 1;
		var->player->pos_y += sin(var->player->dir + (PI/2)) * 1;
	}
	if (keycode == TURN_L)
		var->player->dir = var->player->dir + 0.1;
	if (keycode == TURN_R)
		var->player->dir = var->player->dir - 0.1;
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
	mlx_hook(var->win, 2, 1L << 0, key_hook, var);
	mlx_loop_hook(var->mlx, gameplay, var);
	// mlx_hook(var->win, 2, 1L << 0, key_hook, g);
	mlx_loop(var->mlx);
	return (0);
}
