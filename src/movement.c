#include "cub3D.h"

void	move_up(t_map *map, t_player *player, float speed)
{
	float	anticip_x;
	float	anticip_y;

	anticip_y = player->pos_y + (player->dir_y * speed) * 0.050f;
	anticip_x = player->pos_x + (player->dir_x * speed) * 0.050f;
	if (map->tab_map[(int)(anticip_y / GAME_sz)]
		[(int)(anticip_x / GAME_sz)] != '1')
	{
		player->pos_x += player->dir_x * speed;
		player->pos_y -= player->dir_y * speed;
	}
}

void	move_down(t_map *map, t_player *player, float speed)
{
	float	anticip_x;
	float	anticip_y;

	anticip_y = player->pos_y - player->dir_y * (speed * 5.0f);
	anticip_x = player->pos_x - player->dir_x * (speed * 5.0f);
	if (map->tab_map[(int)(anticip_y / GAME_sz)]
		[(int)(anticip_x / GAME_sz)] != '1')
	{
		player->pos_x -= player->dir_x * speed;
		player->pos_y -= player->dir_y * speed;
	}
}

void	move_left(t_map *map, t_player *player, float speed)
{
	float	anticip_x;
	float	anticip_y;
	float	previous_dir_x;

	previous_dir_x = player->dir_x;
	anticip_y = player->pos_y + sin(player->dir - (PI/2)) * (speed * 5.0f);
	anticip_x = player->pos_x + cos(player->dir + (PI/2)) * (speed * 5.0f);
	if (map->tab_map[(int)(anticip_y / GAME_sz)]
		[(int)(anticip_x / GAME_sz)] != '1')
	{
		player->pos_x += cos(player->dir + (PI/2)) * speed;
		player->pos_y += sin(player->dir - (PI/2)) * speed;
	}
}

void	move_right(t_map *map, t_player *player, float speed)
{
	
	float	anticip_x;
	float	anticip_y;

	anticip_y = player->pos_y + sin(player->dir + (PI/2)) * (speed * 5.0f);
	anticip_x = player->pos_x + cos(player->dir - (PI/2)) * (speed * 5.0f);
	if (map->tab_map[(int)(anticip_y / GAME_sz)]
		[(int)(anticip_x / GAME_sz)] != '1')
	{
		player->pos_x += cos(player->dir - (PI/2)) * speed;
		player->pos_y += sin(player->dir + (PI/2)) * speed;
	}
}