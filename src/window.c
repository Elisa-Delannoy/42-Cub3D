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

int	setup_window(t_var *var)
{
	char *map[] = 
	{"11111",
    "10001",
    "10101",
    "100N1",
    "11111"};
	var->mlx = mlx_init();
	
	var->win = mlx_new_window(var->mlx, 1920, 1080, "Exit the cavern !");
	mlx_hook(var->win, 17, 0, clear_all, var);

	// mlx_hook(var->win, 2, 1L << 0, key_hook, g);
	mlx_loop(var->mlx);
	return (0);
}

int	main(void)
{
	t_var var;
	
	setup_window(&var);
	return (0);
}