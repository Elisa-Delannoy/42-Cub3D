#include "cub3D.h"

t_map	*ft_init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	ft_bzero(map, sizeof(t_map));
	return (map);
}

void	init_player_dir(t_var *var, t_player *player, int x, int y)
{
	if (var->map->tab_map[x][y] == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	if (var->map->tab_map[x][y] == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	if (var->map->tab_map[x][y] == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	if (var->map->tab_map[x][y] == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

t_player	*init_player(t_var *var, int x, int y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->pos_x = (double)y + 0.5;
	player->pos_y = (double)x + 0.5;
	init_player_dir(var, player, x, y);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
	player->speed = 0.05;
	player->m_up = 0;
	player->m_down = 0;
	player->m_left = 0;
	player->m_right = 0;
	player->sprint = 0;
	player->mouse = 0;
	player->o_c_door = 0;
	return (player);
}

t_img	*init_img(void)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	img->img = NULL;
	img->height = 0;
	img->data_img = NULL;
	img->endian = 0;
	img->width = 0;
	return (img);
}

void	init_var(t_var *var)
{
	var->height = 800;
	var->width = 1200;
	var->time = 500;
	var->count = 0;
	var->on_off = 1;
	var->a = 4;
	var->exit = 0;
	var->end_g = 0;
}
