#include "../cub3D.h"

void	ft_init_map(t_map *map)
{
	map->lst_map = NULL;
	map->map = NULL;
}

void	ft_free_all(t_map *map)
{
	ft_lstclear(&map->lst_map, free);
	if (map->map)
		free_split(map->map);
}
