#include "cub3D.h"

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
	else if (dir == DOOR)
		path = var->map->door;
	else if (dir == EXIT)
		path = var->map->exit;
	new_text.img = mlx_xpm_file_to_image(var->mlx, path, &new_text.width,
			&new_text.height);
	if (new_text.img == NULL)
		return (ft_putstr_fd("Error : invalid texture ", 2),
			ft_putendl_fd(path, 2), ft_free_all(var), exit(2), new_text);
	new_text.data_img = mlx_get_data_addr(new_text.img, &new_text.bpp,
			&new_text.line_len, &new_text.endian);
	return (new_text);
}

void	init_all_textures(t_var *var)
{
	var->no_t = init_texture(var, NORTH);
	var->so_t = init_texture(var, SOUTH);
	var->ea_t = init_texture(var, EAST);
	var->we_t = init_texture(var, WEST);
	if (var->map->door != NULL)
		var->door_t = init_texture(var, DOOR);
	if (var->map->exit != NULL)
	{
		var->exit_t = init_texture(var, EXIT);
		var->end.img = mlx_xpm_file_to_image(var->mlx, "end.xpm",
				&var->end.width, &var->end.height);
		var->end.data_img = mlx_get_data_addr(var->end.img,
				&var->end.bpp, &var->end.line_len, &var->end.endian);
	}
}

t_light	*init_light(t_var *var)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->top = 150;
	light->bottom = var->height - 1;
	light->center = var->width / 2;
	light->left_b = light->center -30 ;
	light->left_top = 0;
	light->right_b = light->center + 100;
	light->right_top = var->width;
	return (light);
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
