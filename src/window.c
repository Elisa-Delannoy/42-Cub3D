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
		mlx_put_image_to_window(var->mlx, var->win, var->img_g->img,  0, 0);
		mlx_put_image_to_window(var->mlx, var->win, var->img->img, (1900 - (20 * var->map->width)), 1200 - (20 * var->map->height));
		// draw_dir(var, 1920 - ((34 - var->player->map_y - 0.5) * 20), 1080 - ((14 - var->player->map_x - 0.5) * 20), 0xFF0140);
		find_wall_ray(var, MAP);
		// draw_game(var->img_g, 1200, 1900);
		// find_wall_ray(var, GAME);
	}
	return(0);
}
// noah a supp elisa a garder
// int	check_wall(t_var *var)
// {
// 	float	x;		
// 	float	y;
// 	(void)var;
// 	x = var->player->map_x + 0.1;
// 	y = 2.1;
// 	printf("%d", (int)x);
// 	printf("%d", (int)var->player->map_x);
// 	return (0);
// }

void	update_player(t_var *var, int dx, int dy)
{
	draw_player(var, 125, var->player->map_y, var->player->map_x);
	var->player->map_x = var->player->map_x + dx;
	var->player->map_y = var->player->map_y + dy;
	draw_player(var, 0xFF0140, var->player->map_y, var->player->map_x);
}

int	key_hook(int keycode, t_var *var)
{
	if (keycode == ESC)
		clear_all(var);
	if (keycode == UP)
		update_player(var, 0, -1);
	if (keycode == DOWN)
		update_player(var, 0, 1);
	if (keycode == LEFT)
		update_player(var, -1, 0);
	if (keycode == RIGHT)
		update_player(var, 1, 0);
	if (keycode == TURN_L)
		var->player->dir = var->player->dir + 0.1;
	if (keycode == TURN_R)
		var->player->dir = var->player->dir - 0.1;
	draw_game(var->img_g, 1200, 1900);
	// printf("dir = %f\n", var->player->dir);
	return (0);
}

int	setup_window(t_var *var)
{
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, 1900, 1200, "Exit the cavern !");
	make_minimap(var);
	make_game(var);
	printf("x =%f\n", var->player->map_x);
	printf("y =%f\n", var->player->map_y);
	mlx_hook(var->win, 17, 0, clear_all, var);
	mlx_hook(var->win, 2, 1L << 0, key_hook, var);
	mlx_loop_hook(var->mlx, gameplay, var);
	// mlx_hook(var->win, 2, 1L << 0, key_hook, g);
	mlx_loop(var->mlx);
	return (0);
}
