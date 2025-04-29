#include "../cub3D.h"

void	ft_init_map(t_map *map)
{
	map->lst_map = NULL;
	map->map = NULL;
	map->no = 0;
	map->so = 0;
	map->we = 0;
	map->ea = 0;
	map->f = 0;
	map->c = 0;
}

void	ft_free_all(t_map *map)
{
	ft_lstclear(&map->lst_map, free);
	if (map->map)
		free_split(map->map);
}
