#include "../cub3D.h"

t_map	*ft_init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->lst_map = NULL;
	map->tab_map = NULL;
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
	return (map);
}

t_img	*init_img(void)
{
	t_img	*img;
	img = malloc(sizeof(t_img));
	img->bits_per_pixel = 0;
	img->data_img = NULL;
	img->endian = 0;
	img->size_line = 0;
	return (img);
}

void	ft_free_all(t_map *map)
{
	ft_lstclear(&map->lst_map, free);
	if (map->tab_map)
		free_split(map->tab_map);
	if (map->no)
		free(map->no);
	free(map);
}
