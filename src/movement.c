#include "cub3D.h"

void	move_up(t_map *map, t_player *player, double speed)
{
	double	anticip_x;
	double	anticip_y;
	int		check;

	anticip_y = player->pos_y + (player->dir_y * speed) * 10.f;
	anticip_x = player->pos_x + (player->dir_x * speed) * 10.f;
	check = check_in_map(map, (int)(anticip_y), (int)(anticip_x));
	if (check != 0 && map->tab_map[(int)(anticip_y)]
		[(int)(player->pos_x)] != '1')
		player->pos_y += player->dir_y * speed;
	if (check != 2 && map->tab_map[(int)(player->pos_y)]
		[(int)(anticip_x)] != '1')
		player->pos_x += player->dir_x * speed;
}

void	move_down(t_map *map, t_player *player, double speed)
{
	double	anticip_x;
	double	anticip_y;
	int		check;

	anticip_y = player->pos_y + (player->dir_y * speed) * 10.0F;
	anticip_x = player->pos_x + (player->dir_x * speed) * 10.0F;
	check = check_in_map(map, (int)(anticip_y), (int)(anticip_x));
	if (check != 0 && map->tab_map[(int)(anticip_y)]
		[(int)(player->pos_x)] != '1')
		player->pos_x -= player->dir_x * speed;
	if (check != 2 && map->tab_map[(int)(player->pos_y)]
		[(int)(anticip_x)] != '1')
		player->pos_y -= player->dir_y * speed;
}

void	move_left(t_map *map, t_player *player, double speed)
{
	double	anticip_x;
	double	anticip_y;
	int		check;

	anticip_y = player->pos_y - player->plane_y * (speed * 10.0f);
	anticip_x = player->pos_x - player->plane_x * (speed * 10.0f);
	check = check_in_map(map, (int)(anticip_y), (int)(anticip_x));
	if (check != 0 && map->tab_map[(int)(anticip_y)]
		[(int)(player->pos_x)] != '1')
		player->pos_y -= player->plane_y * speed;
	if (check != 2 && map->tab_map[(int)(player->pos_y)]
		[(int)(anticip_x)] != '1')
		player->pos_x -= player->plane_x * speed;
}

void	move_right(t_map *map, t_player *player, double speed)
{
	
	double	anticip_x;
	double	anticip_y;
	int		check;

	anticip_y = player->pos_y + player->plane_y * (speed * 10.0f);
	anticip_x = player->pos_x + player->plane_x * (speed * 10.0f);
	check = check_in_map(map, (int)(anticip_y), (int)(anticip_x));
	if (check != 0 && map->tab_map[(int)(anticip_y)]
		[(int)(player->pos_x)] != '1')
		player->pos_y += player->plane_y * speed;
	if (check != 2 && map->tab_map[(int)(player->pos_y)]
		[(int)(anticip_x)] != '1')
		player->pos_x += player->plane_x * speed;
}

void	rotate(t_player *player, double angle)
{
	double	previous_dir_x;
	double	previous_plane_x;

	previous_dir_x = player->dir_x;
	previous_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = previous_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = previous_plane_x * sin(angle) + player->plane_y * cos(angle);
}

