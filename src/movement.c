#include "cub3D.h"

void	move_up(t_map *map, t_player *player, float speed)
{
	float anticip_x;
	float anticip_y;

	anticip_y = player->pos_y - (sin(player->dir) * speed) * 5;
	anticip_x = player->pos_x + (cos(player->dir) * speed) * 5;
	if (map->tab_map[(int)(anticip_y / GAME_sz)]
		[(int)(anticip_x / GAME_sz)] != '1')
	{
		player->pos_x += cos(player->dir) * speed;
		player->pos_y -= sin(player->dir) * speed;
	}
}

void	move_down(t_map *map, t_player *player, float speed)
{
	float anticip_x;
	float anticip_y;

	anticip_y = player->pos_y + sin(player->dir) * (speed * 5);
	anticip_x = player->pos_x - cos(player->dir) * (speed * 5);
	if (map->tab_map[(int)(anticip_y / GAME_sz)]
		[(int)(anticip_x / GAME_sz)] != '1')
	{
		player->pos_x -= cos(player->dir) * speed;
		player->pos_y += sin(player->dir) * speed;
	}
}

void	move_left(t_map *map, t_player *player, float speed)
{
	float anticip_x;
	float anticip_y;

	anticip_y = player->pos_y + sin(player->dir - (PI/2)) * (speed * 5);
	anticip_x = player->pos_x + cos(player->dir + (PI/2)) * (speed * 5);
	if (map->tab_map[(int)(anticip_y / GAME_sz)]
		[(int)(anticip_x / GAME_sz)] != '1')
	{
		player->pos_x += cos(player->dir + (PI/2)) * speed;
		player->pos_y += sin(player->dir - (PI/2)) * speed;
	}
}

void	move_right(t_map *map, t_player *player, float speed)
{
	
	float anticip_x;
	float anticip_y;

	anticip_y = player->pos_y + sin(player->dir + (PI/2)) * (speed * 5);
	anticip_x = player->pos_x + cos(player->dir - (PI/2)) * (speed * 5);
	if (map->tab_map[(int)(anticip_y / GAME_sz)]
		[(int)(anticip_x / GAME_sz)] != '1')
	{
		player->pos_x += cos(player->dir - (PI/2)) * speed;
		player->pos_y += sin(player->dir + (PI/2)) * speed;
	}
}