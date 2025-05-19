#include "cub3D.h"

void	move_up(t_player *player)
{
	player->pos_x += cos(player->dir) * 3;
	player->pos_y -= sin(player->dir) * 3;
}

void	move_down(t_player *player)
{
	player->pos_x -= cos(player->dir) * 3;
	player->pos_y += sin(player->dir) * 3;
}

void	move_left(t_player *player)
{
	player->pos_x += cos(player->dir + (PI/2)) * 3;
	player->pos_y += sin(player->dir - (PI/2)) * 3;
}

void	move_right(t_player *player)
{
	player->pos_x += cos(player->dir - (PI/2)) * 3;
	player->pos_y += sin(player->dir + (PI/2)) * 3;
}