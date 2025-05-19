#include "cub3D.h"

void	move_up(t_player *player, float vitesse)
{
	player->pos_x += cos(player->dir) * vitesse;
	player->pos_y -= sin(player->dir) * vitesse;
}

void	move_down(t_player *player, float vitesse)
{
	player->pos_x -= cos(player->dir) * vitesse;
	player->pos_y += sin(player->dir) * vitesse;
}

void	move_left(t_player *player, float vitesse)
{
	player->pos_x += cos(player->dir + (PI/2)) * vitesse;
	player->pos_y += sin(player->dir - (PI/2)) * vitesse;
}

void	move_right(t_player *player, float vitesse)
{
	player->pos_x += cos(player->dir - (PI/2)) * vitesse;
	player->pos_y += sin(player->dir + (PI/2)) * vitesse;
}