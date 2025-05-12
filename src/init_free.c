#include "cub3D.h"

t_map	*ft_init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->lst_map = NULL;
	map->tab_file = NULL;
	map->tab_map = NULL;
	map->temp = NULL;
	map->c_no = 0;
	map->c_so = 0;
	map->c_we = 0;
	map->c_ea = 0;
	map->c_f = 0;
	map->c_c = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
	map->height = 0;
	map->width = 0;
	return (map);
}

t_player	*init_player(t_var *var, int x, int y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->game_x = (float)(x * 64);
	player->game_y = (float)(y * 64);
	player->map_x = (float)((y + 0.25) * 20);
	player->map_y = (float)((x + 0.25) * 20);
	if (var->map->tab_map[x][y] == 'N')
		player->dir = radian(NORTH);
	if (var->map->tab_map[x][y] == 'S')
		player->dir = radian(SOUTH);
	if (var->map->tab_map[x][y] == 'E')
		player->dir = radian(EAST);
	if (var->map->tab_map[x][y] == 'W')
		player->dir = radian(WEAST);
	player->fov = radian(4);
	return (player);
}

t_img	*init_img(void)
{
	t_img	*img;
	
	img = malloc(sizeof(t_img));
	img->img = NULL;
	img->bits_per_pixel = 0;
	img->data_img = NULL;
	img->endian = 0;
	img->size_line = 0;
	return (img);
}

void	ft_free_all(t_var *var)
{
	if (var->map)
	{
		if (var->map->lst_map)
			ft_lstclear(&var->map->lst_map, free);
		if (var->map->tab_file)
			free_split(var->map->tab_file);
		if (var->map->tab_map)
			free_split(var->map->tab_map);
		if (var->map->temp)
			free_split(var->map->temp);
		if (var->map->no)
			free(var->map->no);
		if (var->map->so)
			free(var->map->so);
		if (var->map->we)
			free(var->map->we);
		if (var->map->ea)
			free(var->map->ea);
		if (var->map->f)
			free_split(var->map->f);
		if (var->map->c)
			free_split(var->map->c);
		free(var->map);
	}
	if (var->player != NULL)
		free(var->player);
}
