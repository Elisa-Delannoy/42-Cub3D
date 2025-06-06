#include "cub3D.h"

int	check_in_map(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= map->width)
		return (2);
	return (1);
}

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

