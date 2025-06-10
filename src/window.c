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

void	check_end_game(t_var *var, t_player *player)
{
	if (var->map->tab_map[(int)(player->pos_y)][(int)(player->pos_x)] == 'X')
		var->exit = 1;
}

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

int	check_time(t_var *var)
{
	gettimeofday(&var->tv, NULL);
	if (var->tv.tv_sec - var->start_t < GAME_DURATION / 3)
		draw_img_in_img(var, var->batterie[0], var->width - 160, 0);
	else if (var->tv.tv_sec - var->start_t < ((double)GAME_DURATION * 0.6666666666666))
		draw_img_in_img(var, var->batterie[1], var->width - 160, 0);
	else if (var->tv.tv_sec - var->start_t < GAME_DURATION)
		draw_img_in_img(var, var->batterie[2], var->width - 160, 0);
	if (var->tv.tv_sec - var->start_t >= GAME_DURATION)
		return(1);
	return (0);
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
			if ((var->on_off == -1 && var->a > 0) || (var->on_off == 1 && var->a < 4))
				var->a += var->on_off;
			draw_img_in_img(var, var->torch[var->a], 550, 650);
		if (var->exit == 0 && check_time(var) == 0)
		{
			mlx_put_image_to_window(var->mlx, var->win, var->img_g->img, 0, 0);
			mlx_put_image_to_window(var->mlx, var->win, var->img->img, ((int)(var->width - (MAP_sz * 10))), (int)(var->height - (MAP_sz * 10)));
		}
		else if (var->exit == 1 && check_time(var) == 0)
		{
			draw_img_in_img(var, var->batterie[4], 1, 1);
			mlx_put_image_to_window(var->mlx, var->win, var->img_g->img, 0, 0);
		}	
		else if (check_time(var) == 1 && var->exit == 0)
		{
			draw_img_in_img(var, var->batterie[3], 1, 1);
			mlx_put_image_to_window(var->mlx, var->win, var->img_g->img, 0, 0);
		}	
		mlx_do_sync(var->mlx);
	}
	return(0);
}

int select_key(int keycode, t_var *var, int truc) {
	if (keycode == XK_w)
		var->player->m_up = truc;
	if (keycode == XK_s)
		var->player->m_down = truc;
	if (keycode == XK_a)
		var->player->m_left = truc;
	if (keycode == XK_d)
		var->player->m_right = truc;
	if (keycode == XK_Shift_L)
		var->player->sprint = truc;
	if (keycode == XK_Left)
		var->player->t_left = truc;
	if (keycode == XK_Right)
		var->player->t_right = truc;
	return (0);
}

int	key_press(int keycode, t_var *var)
{
	if (keycode == XK_Escape)
		clear_all(var);
	if (keycode == XK_space)
		var->on_off *= -1;
	select_key(keycode, var, 1);
	if (keycode == XK_BackSpace)
		var->player->mouse = 0;
	if (keycode == XK_e)
		var->player->o_c_door = 1;
	return (0);
}

int	key_release(int keycode, t_var *var)
{
	select_key(keycode, var, 0);
	return (0);
}

t_cast	*init_cast(void)
{
	t_cast	*cast;

	cast = malloc(sizeof(t_cast));
	return (cast);
}

int	active_mouse(int button, int x, int y, t_var *var)
{
	(void)	x;
	(void)	y;

	if (button == 1)
	{
		var->player->mouse = 1;
		return (1);
	}
	return (0);
}

int	mouse_movement(int x, int y, t_var *var)
{
	static int	last_x = -1;
	
	(void) y;
	if (last_x != - 1 && var->player->mouse == 1)
	{
		mlx_mouse_hide(var->mlx, var->win);
		if (x >= var->width / 4 * 3 || x <= var->width / 4)
			mlx_mouse_move(var->mlx, var->win, var->width / 2, var->height / 2);
		if (last_x - x > 0)
			rotate(var->player, -0.015f);
		else if (last_x - x < 0)
			rotate(var->player, +0.015f);
	}

	last_x = x;
	return (0);
}

t_img	*set_timer(t_var* var)
{
	t_img *batterie;
	
	gettimeofday(&var->tv, NULL);
	var->start_t = var->tv.tv_sec;
	batterie = malloc(sizeof(t_img) * 5);
	batterie[0].img = mlx_xpm_file_to_image(var->mlx, "batterie3.xpm", &batterie[0].width, &batterie[0].height);
	batterie[1].img = mlx_xpm_file_to_image(var->mlx, "batterie2.xpm", &batterie[1].width, &batterie[1].height);
	batterie[2].img = mlx_xpm_file_to_image(var->mlx, "batterie1.xpm", &batterie[2].width, &batterie[2].height);
	batterie[0].data_img = mlx_get_data_addr(batterie[0].img, &batterie[0].bpp, &batterie[0].line_len, &batterie[0].endian);
	batterie[1].data_img = mlx_get_data_addr(batterie[1].img, &batterie[1].bpp, &batterie[1].line_len, &batterie[1].endian);
	batterie[2].data_img = mlx_get_data_addr(batterie[2].img, &batterie[2].bpp, &batterie[2].line_len, &batterie[2].endian);
	batterie[3].img = mlx_xpm_file_to_image(var->mlx, "gameover.xpm", &batterie[3].width, &batterie[3].height);
	batterie[4].img = mlx_xpm_file_to_image(var->mlx, "victory.xpm", &batterie[4].width, &batterie[4].height);
	batterie[3].data_img = mlx_get_data_addr(batterie[3].img, &batterie[3].bpp, &batterie[3].line_len, &batterie[3].endian);
	batterie[4].data_img = mlx_get_data_addr(batterie[4].img, &batterie[4].bpp, &batterie[4].line_len, &batterie[4].endian);
	return (batterie);
}

int	setup_window(t_var *var)
{
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, (int)var->width, (int)var->height, "Exit the cavern !");
	var->light = init_light(var);
	var->cast = init_cast();
	var->minimap = init_minimap();
	var->batterie = set_timer(var);
	var->torch = init_torch(var);
	make_minimap(var);
	make_game(var);
	init_all_textures(var);
	mlx_hook(var->win, 17, 0, clear_all, var);
	mlx_mouse_hook(var->win, active_mouse, var);
	mlx_hook(var->win, MotionNotify, PointerMotionMask, mouse_movement, var);
	mlx_hook(var->win, KeyPress, KeyPressMask, key_press, var);
	mlx_hook(var->win, KeyRelease, KeyReleaseMask, key_release, var);
	mlx_loop_hook(var->mlx, gameplay, var);
	mlx_loop(var->mlx);
	return (0);
}
