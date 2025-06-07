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
	return (map);
}

t_player	*init_player(t_var *var, int x, int y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->pos_x = y + 1 / 2;
	player->pos_y = x + 1 / 2;

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
	player->speed = 0.05;
	player->m_up = 0;
	player->m_down = 0;
	player->m_left = 0;
	player->m_right = 0;
	player->sprint = 0;
	player->mouse = 0;
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

t_minimap	*init_minimap(void)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	return (minimap);
}


t_img	init_texture(t_var *var, int dir)
{
	t_img	new_text;
	char	*path;

	path = NULL;
	if (dir == NORTH)
		path = var->map->no;
	else if (dir == SOUTH)
		path = var->map->so;
	else if (dir == EAST)
		path = var->map->ea;
	else if (dir == WEST)
		path = var->map->we;

	new_text.img = mlx_xpm_file_to_image(var->mlx, path, &new_text.width, &new_text.height);
	new_text.data_img = mlx_get_data_addr(new_text.img, &new_text.bpp, &new_text.line_len, &new_text.endian);
	return(new_text);
}

void	init_all_textures(t_var *var)
{
	var->no_t = init_texture(var, NORTH);
	var->so_t = init_texture(var, SOUTH);
	var->ea_t = init_texture(var, EAST);
	var->we_t = init_texture(var, WEST);
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
	if (var->cast != NULL)
		free(var->cast);
	if (var->img != NULL)
		free (var->img);
	if (var->img_g != NULL)
		free (var->img_g);
}
