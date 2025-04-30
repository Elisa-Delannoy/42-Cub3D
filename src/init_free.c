#include "../cub3D.h"

void	ft_init_map(t_map *map)
{
	map->lst_map = NULL;
	map->map = NULL;
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
}

void	ft_free_all(t_map *map)
{
	ft_lstclear(&map->lst_map, free);
	if (map->map)
		free_split(map->map);
}
