#include "cub3D.h"

int	select_key(int keycode, t_var *var, int value)
{
	if (keycode == XK_w)
		var->player->m_up = value;
	if (keycode == XK_s)
		var->player->m_down = value;
	if (keycode == XK_a)
		var->player->m_left = value;
	if (keycode == XK_d)
		var->player->m_right = value;
	if (keycode == XK_Shift_L)
		var->player->sprint = value;
	if (keycode == XK_Left)
		var->player->t_left = value;
	if (keycode == XK_Right)
		var->player->t_right = value;
	return (0);
}

int	key_press(int keycode, t_var *var)
{
	if (keycode == XK_Escape)
		clear_all(var);
	if (keycode == XK_space && var->end_g != 1)
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

int	active_mouse(int button, int x, int y, t_var *var)
{
	(void) x;
	(void) y;
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
	if (last_x != -1 && var->player->mouse == 1)
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
