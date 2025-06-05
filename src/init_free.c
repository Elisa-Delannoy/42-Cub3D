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
	map->color_c = 0;
	map->color_f = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->color_c = 0;
	map->color_f = 0;
	map->height = 0;
	map->width = 0;
	// map->g_to_m = (GAME_sz / MAP_sz);
	return (map);
}

t_player	*init_player(t_var *var, int x, int y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->pos_x = y * GAME_sz + GAME_sz / 2;
	player->pos_y = x * GAME_sz + GAME_sz / 2;

	if (var->map->tab_map[x][y] == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	if (var->map->tab_map[x][y] == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	if (var->map->tab_map[x][y] == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	if (var->map->tab_map[x][y] == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
	

	// player->fov = radian(60);
	player->speed = 0.05; /*init 3*/
	player->m_up = 0;
	player->m_down = 0;
	player->m_left = 0;
	player->m_right = 0;
	player->sprint = 0;
	return (player);
}

t_img	*init_img(void)
{
	t_img	*img;
	
	img = malloc(sizeof(t_img));
	img->img = NULL;
	img->height = 0;
	img->data_img = NULL;
	img->endian = 0;
	img->width = 0;
	return (img);
}

t_img	*init_img_g(void)
{
	t_img	*img_g;
	
	img_g = malloc(sizeof(t_img));
	img_g->img = NULL;
	img_g->height = 0;
	img_g->data_img = NULL;
	img_g->endian = 0;
	img_g->width = 0;
	return (img_g);
}

t_img	init_texture(t_var *var)
{
	t_img no_t;

	no_t.width = 80;
	no_t.height = 80;
	no_t.img = mlx_xpm_file_to_image(var->mlx, var->map->no, &var->no_t.width, &var->no_t.height);
	no_t.data_img = mlx_get_data_addr(no_t.img, &no_t.bpp, &no_t.line_len, &no_t.endian);
	return (no_t);
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
		free(var->map);
	}
	if (var->player != NULL)
		free(var->player);
}
