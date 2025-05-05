#include "../cub3D.h"

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
		mlx_put_image_to_window(var->mlx, var->win, var->img->img, 0, 0);
		draw_player(var, 0xFF0140, 1920 - ((34 - var->player->y - 0.75) * 20), 1080 - ((14 - var->player->x - 0.75) * 20));
	}
	return(0);
}
// noah a supp elisa a garder
// int	check_wall(t_var *var)
// {
// 	float	x;		
// 	float	y;
// 	(void)var;
// 	x = var->player->x + 0.1;
// 	y = 2.1;
// 	printf("%d", (int)x);
// 	printf("%d", (int)var->player->x);
// 	return (0);
// }

int	key_hook(int keycode, t_var *var)
{
	if (keycode == ESC)
		clear_all(var);
	if (keycode == UP)
		var->player->x = var->player->x - 0.1;
	if (keycode == DOWN)
		var->player->x = var->player->x + 0.1;
	if (keycode == LEFT)
		var->player->y = var->player->y - 0.1;
	if (keycode == RIGHT)
		var->player->y = var->player->y + 0.1;
	printf("teat %f\n", var->player->x);
	return (0);
}

int	setup_window(t_var *var)
{
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, 1920, 1080, "Exit the cavern !");
	make_minimap(var);
	mlx_hook(var->win, 17, 0, clear_all, var);
	mlx_key_hook(var->win, key_hook, var);
	mlx_loop_hook(var->mlx, gameplay, var);
	// mlx_hook(var->win, 2, 1L << 0, key_hook, g);
	mlx_loop(var->mlx);
	return (0);
}
