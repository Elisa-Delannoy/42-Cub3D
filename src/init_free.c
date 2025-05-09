#include "../cub3D.h"

t_map	*ft_init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->lst_map = NULL;
	map->tab_file = NULL;
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
	map->width = 0;
	return (map);
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

void	ft_free_all(t_map *map)
{
	ft_lstclear(&map->lst_map, free);
	if (map->tab_file)
		free_split(map->tab_file);
	if (map->tab_map)
		free_split(map->tab_map);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->f)
		free_split(map->f);
	if (map->c)
		free_split(map->c);
	free(map);
	// free(player);
}
